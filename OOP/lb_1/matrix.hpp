#pragma once

namespace my {
    double abs(complex &num) {
        return num.get_radius();
    }
    double abs(double num) {
        return std::abs(num);
    }
}

template <class T>
matrix<T>::matrix(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->elems.resize(rows * cols);
}

template <class T>
matrix<T>::matrix(std::vector<T> elems, int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->elems = elems;
}

template <>
matrix<double>::matrix(const std::string &input_filename)
{
    int cols = 0, rows = 0;
    std::vector<double> vec; // elements
    std::ifstream fin(input_filename);

    if (fin.is_open())
    {
        do {
            char ch = fin.peek();
            if (ch == '\n' || ch == EOF) {
                ++rows;
            }
        } while (fin.get() != EOF);
        
        double x;
        fin.clear();              // clear flags
        fin.seekg(std::ios::beg); // set read position to start
        while (fin >> x)
            vec.push_back(x);

        cols = vec.size() / rows;
        if (!fin.eof() && fin.fail() || cols == 0)
            throw std::runtime_error(INVALID_INPUT);
        if (rows * cols != vec.size())
            throw std::runtime_error(INVALID_INPUT);
    }
    else throw std::runtime_error(UNABLE_TO_OPEN_FILE);
    fin.close();

    this->cols = cols;
    this->rows = rows;
    this->elems = vec;
}

template <>
matrix<complex>::matrix(const std::string &input_filename)
{
    int cols = 0, rows = 0;
    std::vector<complex> vec; // elements
    std::ifstream fin(input_filename);

    if (fin.is_open())
    {
        do {
            char ch = fin.peek();
            if (ch == '\n' || ch == EOF) {
                ++rows;
            }
        } while (fin.get() != EOF);
        
        fin.clear();              // clear flags
        fin.seekg(std::ios::beg); // set read position to start
        cinterpreter ci(fin);
        while (fin) {
            while (fin.peek() == ';' || fin.peek() == '\n') {
                fin.get(); // ';'
            }
            if (fin.peek() == EOF) break;
            complex num = ci.expression();
            vec.push_back(num);
        }

        cols = vec.size() / rows;
        if (!fin.eof() && fin.fail() || cols == 0)
            throw std::runtime_error(INVALID_INPUT);
        if (rows * cols != vec.size())
            throw std::runtime_error(INVALID_INPUT);
    }
    else throw std::runtime_error(UNABLE_TO_OPEN_FILE);
    fin.close();

    this->cols = cols;
    this->rows = rows;
    this->elems = vec;
}

template <class T>
matrix<T>::matrix(const matrix &other)
{
    // std::cout << "Copy ctor called" << std::endl;
    (*this) = other;
}

template <class T>
T matrix<T>::determinant()
{
    if (rows != cols) // не квадратная матрица
        throw std::logic_error(NON_SQUARE_MATRIX);
    if (rows == 0)
        return 0.0;
    if (rows == 1)
        return elems[0];
    if (rows == 2)
        return elems[0] * elems[3] - elems[1] * elems[2];

    matrix t = (*this); // create a copy of given matrix;

    T result = 1;
    T mult = 0.0;
    T temp;
    int n = 0;
    for (int i = 0; i < cols-1; ++i)
    {
        for (int j = n + 1; j < rows; ++j)
        {
            T chis = t[j][i];
            T znam = t[n][i];
            if (my::abs(t[n][i]) < ZERO_EPSILON)
            {
                for (int k = n + 1; k < rows; ++k)
                {
                    if (my::abs(t[k][i]) > ZERO_EPSILON)
                    {
                        for (int p = i; p < cols; ++p)
                        {
                            t[n][p] += t[k][p];
                        }
                        break;
                    }
                }
            }
            mult = t[j][i] / t[n][i];
            for (int k = n; k < cols; ++k)
            {
                temp = t[j][k] - t[n][k] * mult;
                t[j][k] -= t[n][k] * mult;
            }
        }
        // std::cout << "\n" << t << "\n";
        result *= t[n][n];
        ++n;
    }
    return result * t[n][n];
}

template <class T>
matrix<T> matrix<T>::transposed()
{
    std::vector<T> vec(cols * rows);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            vec[j * rows + i] = elems[j * rows + i];
        }
    }
    return matrix(vec, cols, rows);
}

template <class T>
matrix<T> matrix<T>::inversed()
{
    T det = determinant();
    if (my::abs(det) == 0.0)
        throw std::logic_error(DEGENERATE_MATRIX);
    std::vector<T> vec(rows * rows);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            T com = get_alg_com(i, j);
            vec[j * cols + i] = get_alg_com(i, j) / det;
        }
    }
    return matrix(vec, rows, rows);
}

template <class T>
void matrix<T>::export_to_csv(const std::string &name)
{
    using std::string;
    string ext = name.substr(name.size() - 4, 4);
    string out_ext = ".csv"; // out extension of file
    string out_name = name;
    if (ext != out_ext)
        out_name += out_ext;

    std::ofstream fout(out_name);
    string prev_delim = print_delim;
    if (fout.is_open())
    {
        print_delim = ", ";
        fout << (*this);
        print_delim = prev_delim;
    }
    fout.close();
}

template <class T>
std::ostream &operator<<(std::ostream &out, const matrix<T> &m)
{
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.cols; ++j)
        {
            T elem = m.get(i, j);
            double delta = my::abs(elem);
            if (delta < ZERO_EPSILON)
                elem = 0.0;
            out << std::fixed
                << std::setw(m.print_width)
                << std::setprecision(m.print_prec)
                << elem << m.print_delim;
        }
        if (i < m.rows - 1)
            out << '\n';
    }
    out << std::flush;
    return out;
}

template <class T>
void operator<<(const char *output_filename, const matrix<T> &m)
{
    std::ofstream fout(output_filename);
    if (fout.is_open())
    {
        fout << m;
    }
    fout.close();
}

template <class T>
matrix<T> matrix<T>::operator*(const matrix &other)
{
    int orows = other.get_rows(); // other rows
    int ocols = other.get_cols(); // other columns

    if (this->cols != orows)
        throw std::logic_error(MULTIPLICATION_IS_NOT_APPLICABLE);
    std::vector<T> res(rows * ocols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < ocols; ++j)
        {
            T sum = 0, temp = 0;
            for (int k = 0; k < cols; ++k)
            {
                temp = other.get(k, j);
                sum += get(i, k) * temp;
            }
            res[i * ocols + j] = sum;
        }
    }
    return matrix(res, rows, ocols);
}

template <class T>
matrix<T> matrix<T>::operator*(matrix *other)
{
    return (*this) * (*other);
}

template <class T>
matrix<T> matrix<T>::operator*(double num)
{
    std::vector<T> vec(rows * cols);
    for (int i = 0; i < rows * cols; ++i)
    {
        vec[i] = elems[i] * num;
    }
    return matrix(vec, rows, cols);
}

template <class T>
matrix<T> matrix<T>::operator^(int pow)
{
    if (pow == -1)
        return inversed();
    if (pow < -1)
        throw std::invalid_argument(INVALID_DEGREEE_INDICATOR);
    if (rows != cols)
        throw std::logic_error(NON_SQUARE_MATRIX);

    matrix res(*this);
    if (pow == 0)
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                res[i][j] = (i == j);
            }
        }
    else
        while (pow-- > 1)
        {
            res *= (*this);
        }
    
    return res;
}

template <class T>
void matrix<T>::operator*=(double num)
{
    for (int i = 0; i < rows * cols; ++i)
    {
        elems[i] *= num;
    }
}

template <class T>
void matrix<T>::operator*=(const matrix<T> &other)
{
    matrix temp(*this);
    *this = temp * this;
}

template <class T>
matrix<T> &matrix<T>::operator=(const matrix<T> &other)
{
    // std::cout << "Operator '=' called" << std::endl;
    this->cols = other.cols;
    this->rows = other.rows;
    this->elems = other.elems;
    this->print_prec = other.print_prec;
    this->print_width = other.print_width;
    this->print_delim = other.print_delim;
    return (*this);
}

template <class T>
typename matrix<T>::row &matrix<T>::operator[](int row)
{
    matrix::check_range(row);
    proxy.row_num = row;
    return proxy;
}

template <class T>
void matrix<T>::check_range(int row)
{
    if (row < 0 || row > rows)
        throw std::out_of_range(OUT_OF_RANGE);
}

template <class T>
int matrix<T>::get_cols() const
{
    return cols;
}

template <class T>
int matrix<T>::get_rows() const
{
    return rows;
}

template <class T>
int matrix<T>::get_print_precision()
{
    return print_prec;
}

template <class T>
int matrix<T>::get_print_width()
{
    return print_width;
}

template <class T>
void matrix<T>::set_print_delimeter(const std::string &delim)
{
    this->print_delim = delim;
}

template <class T>
void matrix<T>::set_print_precision(int prec)
{
    this->print_prec = prec;
}

template <class T>
void matrix<T>::set_print_width(int width)
{
    this->print_width = width;
}

template <class T>
matrix<T>::~matrix()
{
    // std::cout << "Matrix " << this << " dtor called" << std::endl;
}

template <class T>
T matrix<T>::get_alg_com(int row, int col)
{
    if (rows == 1)
        return 1; // matrix 1 x 1

    T result = get_minor(row, col);
    if ((row + col) % 2 != 0)
        result = -result;

    return result;
}

template <class T>
T matrix<T>::get_minor(int row, int col) {
    int dim = rows - 1;
    std::vector<T> vec(dim * dim);

    int k = 0;
    for (int i = 0; i < rows; ++i)
    {
        if (i == row)
            continue;
        for (int j = 0; j < cols; ++j)
        {
            if (j != col)
            {
                T val = get(i, j);
                vec[k++] = val;
            }
        }
    }
    matrix t(vec, dim, dim);
    return t.determinant();
}

template <class T>
T &matrix<T>::get(int row, int col)
{
    return elems[row * cols + col];
}

template <class T>
T matrix<T>::get(int row, int col) const
{
    return elems[row * cols + col];
}

template <class T>
matrix<T>::row::row(std::vector<T> &d, int &cc)
    : data(d), col_count(cc)
{
    // std::cout << "Row " << this << " ctor called. Data address: " << &d << std::endl;
}

template <class T>
T &matrix<T>::row::operator[](int col)
{
    row::check_range(col);
    return data[row_num * col_count + col];
}

template <class T>
void matrix<T>::row::check_range(int col)
{
    if (col < 0 || col > col_count)
        throw std::out_of_range(OUT_OF_RANGE);
}

template <class T>
matrix<T>::row::~row()
{
    // std::cout << "Row " << this << " dtor called" << std::endl;
}

#include "matrix.h"

matrix::matrix(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->elems.resize(rows * cols);
}

matrix::matrix(std::vector<double> elems, int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->elems = elems;
}

matrix::matrix(const std::string &input_filename)
{
    int cols = 0, rows = 0;
    std::vector<double> vec; // elements
    std::ifstream fin(input_filename);

    if (fin.is_open())
    {
        bool is_delim_or_digit;   // is digit / delimeter
        bool num_started = false; // number started
        do {
            char ch = fin.peek();
            is_delim_or_digit = ch == '.' || ('0' <= ch  && ch <= '9');
            if (!num_started && is_delim_or_digit) {
                num_started = true;
            }
            if (num_started && !is_delim_or_digit) {
                num_started = false;
                ++cols;
            }
        } while (fin.get() != '\n' && !fin.eof());
        
        double x;
        fin.clear();              // clear flags
        fin.seekg(std::ios::beg); // set read position to start
        while (fin >> x)
            vec.push_back(x);

        if (!fin.eof() && fin.fail() || cols == 0)
            throw std::runtime_error(INVALID_INPUT);
        rows = vec.size() / cols;
        if (rows * cols != vec.size())
            throw std::runtime_error(INVALID_INPUT);
    }
    else throw std::runtime_error(UNABLE_TO_OPEN_FILE);
    fin.close();

    this->cols = cols;
    this->rows = rows;
    this->elems = vec;
}

matrix::matrix(const matrix &other)
{
    // std::cout << "Copy ctor called" << std::endl;
    (*this) = other;
}

double matrix::determinant()
{
    if (rows != cols) // не квадратная матрица
        throw std::logic_error(NON_SQUARE_MATRIX);
    if (rows == 0)
        return 0;
    if (rows == 1)
        return elems[0];
    if (rows == 2)
        return elems[0] * elems[3] - elems[1] * elems[2];

    matrix t = (*this); // create a copy of given matrix;

    double result = t[0][0];
    double mult = 0;
    int n = 0;
    for (int i = 0; i < cols-1; ++i)
    {
        for (int j = n + 1; j < rows; ++j)
        {
            mult = t[j][i] / t[n][i];
            for (int k = n; k < cols; ++k)
            {
                t[j][k] -= t[n][k] * mult;
            }
        }
        ++n;
        result *= t[n][n];
    }
    return result;
}

matrix matrix::transposed()
{
    std::vector<double> vec(cols * rows);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            vec[j * rows + i] = elems[j * rows + i];
        }
    }
    return matrix(vec, cols, rows);
}

matrix matrix::inversed()
{
    double det = determinant();
    if (det == 0)
        throw std::logic_error(DEGENERATE_MATRIX);
    std::vector<double> vec(rows * rows);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            vec[j * cols + i] = get_alg_com(i, j) / det;
        }
    }
    return matrix(vec, rows, rows);
}

void matrix::export_to_csv(const std::string &name)
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

std::ostream &operator<<(std::ostream &out, const matrix &m)
{
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.cols; ++j)
        {
            double elem = m.get(i, j);
            double delta = std::abs(elem - 0);
            if (delta < ZERO_EPSILON)
                elem = 0;
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

void operator<<(const char *output_filename, const matrix &m)
{
    std::ofstream fout(output_filename);
    if (fout.is_open())
    {
        fout << m;
    }
    fout.close();
}

matrix matrix::operator*(const matrix &other)
{
    int orows = other.get_rows(); // other rows
    int ocols = other.get_cols(); // other columns

    if (this->cols != orows)
        throw std::logic_error(MULTIPLICATION_IS_NOT_APPLICABLE);
    std::vector<double> res(rows * ocols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < ocols; ++j)
        {
            double sum = 0, temp = 0;
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

matrix matrix::operator*(matrix *other)
{
    return (*this) * (*other);
}

matrix matrix::operator*(double num)
{
    std::vector<double> vec(rows * cols);
    for (int i = 0; i < rows * cols; ++i)
    {
        vec[i] = elems[i] * num;
    }
    return matrix(vec, rows, cols);
}

matrix matrix::operator^(int pow)
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

void matrix::operator*=(double num)
{
    for (int i = 0; i < rows * cols; ++i)
    {
        elems[i] *= num;
    }
}

void matrix::operator*=(const matrix &other)
{
    matrix temp(*this);
    *this = temp * this;
}

matrix &matrix::operator=(const matrix &other)
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

matrix::row &matrix::operator[](int row)
{
    matrix::check_range(row);
    proxy.row_num = row;
    return proxy;
}

void matrix::check_range(int row)
{
    if (row < 0 || row > rows)
        throw std::out_of_range(OUT_OF_RANGE);
}

int matrix::get_cols() const
{
    return cols;
}

int matrix::get_rows() const
{
    return rows;
}

int matrix::get_print_precision()
{
    return print_prec;
}

int matrix::get_print_width()
{
    return print_width;
}

void matrix::set_print_delimeter(const std::string &delim)
{
    this->print_delim = delim;
}

void matrix::set_print_precision(int prec)
{
    this->print_prec = prec;
}

void matrix::set_print_width(int width)
{
    this->print_width = width;
}

matrix::~matrix()
{
    // std::cout << "Matrix " << this << " dtor called" << std::endl;
}

double matrix::get_alg_com(int row, int col)
{
    if (rows == 1)
        return 1; // matrix 1 x 1

    double result = get_minor(row, col);
    if ((row + col) % 2 != 0)
        result = -result;

    return result;
}

double matrix::get_minor(int row, int col) {
    int dim = rows - 1;
    std::vector<double> vec(dim * dim);

    int k = 0;
    for (int i = 0; i < rows; ++i)
    {
        if (i == row)
            continue;
        for (int j = 0; j < cols; ++j)
        {
            if (j != col)
            {
                vec[k++] = get(i, j);
            }
        }
    }
    matrix t(vec, dim, dim);
    return t.determinant();
}

double &matrix::get(int row, int col)
{
    return elems[row * cols + col];
}

double matrix::get(int row, int col) const
{
    return elems[row * cols + col];
}

matrix::row::row(std::vector<double> &d, int &cc)
    : data(d), col_count(cc)
{
    // std::cout << "Row " << this << " ctor called. Data address: " << &d << std::endl;
}

double &matrix::row::operator[](int col)
{
    row::check_range(col);
    return data[row_num * col_count + col];
}

void matrix::row::check_range(int col)
{
    if (col < 0 || col > col_count)
        throw std::out_of_range(OUT_OF_RANGE);
}

matrix::row::~row()
{
    // std::cout << "Row " << this << " dtor called" << std::endl;
}

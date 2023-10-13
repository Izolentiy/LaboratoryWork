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
    // std::cout << "Matrix " << this << " ctor called" << std::endl;
    int cols = 0, rows = 0;
    std::string str;         // string
    std::vector<double> vec; // elements
    std::ifstream fin(input_filename);

    if (fin.is_open())
    while (std::getline(fin, str))
    {
        size_t sb = vec.size();             // size before manipulation
        str_helper::add_elements(vec, str); // add new row to matrix
        int cur_cols = vec.size() - sb;     // column count in row

        if (rows == 0)
            cols = cur_cols;
        else if (cols != cur_cols)
            throw std::runtime_error("Invalid input");

        ++rows;
    }
    else throw std::runtime_error("Unable to open file");
    fin.close();

    this->cols = cols;
    this->rows = rows;
    this->elems = vec;
}

matrix::matrix(const matrix &other)
{
    std::cout << "Copy ctor called" << std::endl;
    (*this) = other;
}

/**
 * Чтобы найти определитель, можно воспользоваться
 * метдом разложения по строке/столбцу.
 * Или же методом Гаусса
 * TODO: Реализовать метод Гаусса
 *
 * Но перед этим стоит сделать проверку, на частные
 * случаи (матрица 2 на 2, не квадратная матрица)
 *
 * Метод разложения по строке:
 * 1. Выбираем строку
 * 2. Находим алгебраические дополнения к элементам
 * 3. Складываем произведения элементов на алг. доп. к ним
 * 4. Возвращаем определитель
 */
double matrix::determinant()
{
    if (rows != cols) // не квадратная матрица
        throw std::logic_error("Non square matrix");
    if (rows == 0)
        return 0;
    if (rows == 2) // частный случай
        return elems[0] * elems[3] - elems[1] * elems[2];

    double result = 0.0;
    for (int i = 0; i < cols; ++i)
    {
        result += get_alg_com(0, i) * elems[i];
    }
    return result;
}

matrix matrix::transposed()
{
    std::vector<double> vec;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            vec.push_back(elems[j * rows + i]);
        }
    }
    return matrix(vec, cols, rows);
}

matrix matrix::inversed()
{
    double det = determinant();
    if (det == 0)
        throw std::logic_error("Degenerate matrix");
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
            out << std::fixed
                << std::setw(m.print_width)
                << std::setprecision(m.print_prec)
                << m.get(i, j) << m.print_delim;
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
        throw std::logic_error("Multiplication is not applicable");
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
    std::vector<double> vec;
    for (int i = 0; i < rows * cols; ++i)
    {
        vec.push_back(elems[i] * num);
    }
    return matrix(vec, rows, cols);
}

matrix matrix::operator^(int pow)
{
    if (pow == -1)
        return inversed();
    if (pow < -1)
        throw std::invalid_argument("Invalid degree indicator");
    if (rows != cols)
        throw std::logic_error("Non square matrix");

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
            res *= this;
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

void matrix::operator*=(matrix *other)
{
    (*this) *= (*other);
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
    proxy.row_num = row;
    return proxy;
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

    static std::vector<matrix *> low_matrices;
    if (low_matrices.size() < rows - 2)
    {
        static int high_order = 2;
        while(high_order < rows)
        {
            // std::cout << "Add new matrix to low matrices" << std::endl;
            low_matrices.push_back(new matrix(high_order, high_order));
            high_order++;
        }
    }

    double result = get_minor(row, col, low_matrices);
    if ((row + col) % 2 != 0)
        result = -result;

    return result;
}

double matrix::get_minor(
    int row, int col, std::vector<matrix *> low_matrices
) {
    matrix &low_matrix = (*low_matrices[rows - 3]);
    int k = 0;
    for (int i = 0; i < rows; ++i)
    {
        if (i == row)
            continue;
        for (int j = 0; j < cols; ++j)
        {
            if (j != col)
            {
                low_matrix.elems[k++] = this->get(i, j);
            }
        }
    }
    return low_matrix.determinant();
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
    return data[row_num * col_count + col];
}

matrix::row::~row()
{
    // std::cout << "Row " << this << " dtor called" << std::endl;
}

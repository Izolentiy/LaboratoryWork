#include "matrix.h"

matrix::matrix(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->elems.resize(rows * cols);
    // std::cout << "Constructor for " << this << " was called";
    // std::cout << std::endl;
}

matrix::matrix(std::vector<double> elems, int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->elems = elems;
    // std::cout << "Constructor for " << this << " was called";
    // std::cout << std::endl;
}

/**
 * @throw "Invalid input"
 */
matrix::matrix(std::ifstream &fin)
{
    int cols = 0, rows = 0;
    std::string str;         // string
    std::vector<double> vec; // elements

    while (std::getline(fin, str))
    {
        size_t sb = vec.size();             // size before manipulation
        str_helper::add_elements(vec, str); // add new row to matrix
        int cur_cols = vec.size() - sb;     // column count in row

        if (rows == 0)
            cols = cur_cols;
        else if (cols != cur_cols)
            throw "Invalid input";

        ++rows;
    }

    this->cols = cols;
    this->rows = rows;
    this->elems = vec;
    // std::cout << "Constructor for " << this << " was called";
    // std::cout << std::endl;
}

void matrix::print_elements()
{
    std::cout << '\n';
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << std::fixed
                      << std::setw(print_width)
                      << std::setprecision(print_prec)
                      << elems[i * cols + j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
}

int matrix::get_cols()
{
    return cols;
}

int matrix::get_rows()
{
    return rows;
}

int matrix::get_precision()
{
    return this->print_prec;
}

int matrix::get_print_width()
{
    return this->print_width;
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
 * 3. Складываем
 * 4. Возвращаем определитель
 */
double matrix::determinant()
{
    if (rows != cols) // не квадратная матрица
        throw "Non square matrix";
    if (rows == 2) // частный случай
        return elems[0] * elems[3] - elems[1] * elems[2];

    double result = 0.0;
    for (int i = 0; i < cols; ++i)
    {
        result += get_alg_com(0, i) * elems[i];
    }
    return result;
}

/**
 * @param row starts with 1
 * @param col starts with 1
 */
double matrix::get_(int row, int col)
{
    return elems[(row - 1) * cols + col - 1];
}

/**
 * @param row starts with 0
 * @param col starts with 0
 */
double matrix::get(int row, int col)
{
    return elems[row * cols + col];
}

void matrix::set_print_precision(int prec)
{
    this->print_prec = prec;
}

void matrix::set_print_width(int width)
{
    this->print_width = width;
}

matrix *matrix::transposition()
{
    std::vector<double> vec;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            vec.push_back(elems[j * rows + i]);
        }
    }
    return new matrix(vec, cols, rows);
}

/**
 * @throw "Degenerate matrix"
 */
matrix *matrix::get_inverse()
{
    double det = determinant();
    if (det == 0)
        throw "Degenerate matrix";
    std::vector<double> vec(rows * rows);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            vec[j * cols + i] = get_alg_com(i, j) / det;
        }
    }
    return new matrix(vec, rows, rows);
}

/**
 * @throw "Multiplication is not applicable"
 */
matrix *matrix::operator*(matrix &other)
{
    int orw = other.get_rows(); // other rows
    int oc = other.get_cols();  // other columns

    if (this->cols != orw)
        throw "Multiplication is not applicable";
    std::vector<double> res(rows * oc);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < oc; ++j)
        {
            double sum = 0, temp = 0;
            for (int k = 0; k < cols; ++k)
            {
                temp = other.get(k, j);
                sum += get(i, k) * temp;
            }
            res[i * oc + j] = sum;
        }
    }
    return new matrix(res, rows, oc);
}

matrix *matrix::operator*(matrix *other)
{
    return (*this) * (*other);
}

matrix *matrix::operator*(double num)
{
    std::vector<double> vec;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            vec.push_back(elems[i * cols + j] * num);
        }
    }
    return new matrix(vec, rows, cols);
}

void matrix::operator*=(double num)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            elems[i * cols + j] *= num;
        }
    }
}

matrix::row &matrix::operator[](int row)
{
    rp.row_num = row;
    return rp;
}

matrix::~matrix()
{
    // std::cout << "Destructor for " << this << " was called";
    // std::cout << std::endl;
}

double matrix::get_alg_com(int row, int col)
{
    if (get(row, col) == 0)
        return 0;

    static std::vector<matrix *> minors;
    if (minors.size() == 0)
    {
        for (int i = 2; i < rows; ++i)
        {
            minors.push_back(new matrix(i, i));
        }
    }

    matrix &minor = get_minor(row, col, minors);
    double result = minor.determinant();
    if ((row + col) % 2 != 0)
        result = -result;

    return result;
}

matrix &matrix::get_minor(
    int row, int col, std::vector<matrix *> minors
) {
    matrix &minor = *(minors[rows-3]);
    int k = 0;
    for (int i = 0; i < rows; ++i)
    {
        if (i == row)
            continue;
        for (int j = 0; j < cols; ++j)
        {
            if (j != col)
            {
                minor.elems[k++] = this->get(i, j);
            }
        }
    }
    return minor;
}

matrix::row::row(std::vector<double> &d, int &cc) : data(d)
{
    this->col_count = cc;
}

double &matrix::row::operator[](int col)
{
    return data[row_num * col_count + col];
}

matrix::row::~row()
{
}

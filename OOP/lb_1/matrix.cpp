#include "matrix.h"

matrix::matrix(int rows, int cols)
{
    this->r = rows;
    this->c = cols;
    this->e.resize(rows * cols);
}

matrix::matrix(std::vector<double> elems, int rows, int cols)
{
    this->r = rows;
    this->c = cols;
    this->e = elems;
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

    this->c = cols;
    this->r = rows;
    this->e = vec;
}

void matrix::print_elements()
{
    for (int i = 0; i < c; ++i)
    {
        for (int j = 0; j < r; ++j)
        {
            std::cout << std::fixed
                      << std::setw(pw)
                      << std::setprecision(pp)
                      << e[i * c + j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
}

int matrix::get_cols()
{
    return c;
}

int matrix::get_rows()
{
    return r;
}

int matrix::get_precision()
{
    return this->pp;
}

int matrix::get_print_width()
{
    return this->pw;
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
    if (r != c) // не квадратная матрица
        throw "Non square matrix";
    if (r == 2) // частный случай
        return e[0] * e[3] - e[1] * e[2];

    double result = 0.0;
    for (int i = 0; i < c; ++i)
    {
        result += get_alg_com(0, i) * e[i];
    }
    return result;
}

/**
 * @param row starts with 1
 * @param col starts with 1
 */
double matrix::get_(int row, int col)
{
    return e[(row - 1) * c + col - 1];
}

/**
 * @param row starts with 0
 * @param col starts with 0
 */
double matrix::get(int row, int col)
{
    return e[row * c + col];
}

void matrix::set_print_precision(int prec)
{
    this->pp = prec;
}

void matrix::set_print_width(int width)
{
    this->pw = width;
}

matrix *matrix::transposition()
{
    std::vector<double> vec;
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            vec.push_back(e[j * r + i]);
        }
    }
    return new matrix(vec, c, r);
}

/**
 * @throw "Degenerate matrix"
 */
matrix *matrix::get_inverse()
{
    double det = determinant();
    if (det == 0)
        throw "Degenerate matrix";
    std::vector<double> v(r * r);
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            v[j * c + i] = get_alg_com(i, j) / det;
        }
    }
    return new matrix(v, r, r);
}

/**
 * @throw "Multiplication is not applicable"
 */
matrix *matrix::operator*(matrix &other)
{
    int orw = other.get_rows(); // other rows
    int oc = other.get_cols();  // other columns

    if (this->c != orw)
        throw "Multiplication is not applicable";
    std::vector<double> res(r * oc);

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < oc; ++j)
        {
            double sum = 0, temp = 0;
            for (int k = 0; k < c; ++k)
            {
                temp = other.get(k, j);
                sum += get(i, k) * temp;
            }
            res[i * oc + j] = sum;
        }
    }
    return new matrix(res, r, oc);
}

matrix *matrix::operator*(matrix *other)
{
    return (*this) * (*other);
}

matrix *matrix::operator*(double num)
{
    std::vector<double> vec;
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            vec.push_back(e[i * c + j] * num);
        }
    }
    return new matrix(vec, r, c);
}

void matrix::operator*=(double num)
{
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            e[i * c + j] *= num;
        }
    }
}

row &matrix::operator[](int row)
{
    rp.set(row);
    return rp;
}

matrix::~matrix()
{
    // std::cout << "Destructor for " << this << " was called";
    // std::cout << std::endl;
}

double matrix::get_alg_com(int row, int col)
{
    double elem = e[row * c + col];
    if (elem == 0)
        return 0;
    matrix *minor = get_minor(row, col);
    double result = minor->determinant();
    if ((row + col) % 2 != 0)
        result = -result;

    delete minor;
    return result;
}

/**
 * TODO: Избавиться от излишнего создания объектов
 */
matrix *matrix::get_minor(int row, int col)
{
    std::vector<double> elems;
    for (int i = 0; i < r; ++i)
    {
        if (i == row)
            continue;
        for (int j = 0; j < c; ++j)
        {
            if (j != col)
            {
                elems.push_back(e[i * c + j]);
            }
        }
    }
    matrix m(1, 1);
    return new matrix(elems, r - 1, c - 1);
}

row::row(std::vector<double> *d, int &cc)
{
    this->d = d;
    this->cc = cc;
}

double row::operator[](int col)
{
    return (*d)[rn * cc + col];
}

void row::set(int n)
{
    this->rn = n;
}

row::~row()
{
}

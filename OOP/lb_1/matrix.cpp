#include "matrix.h"

matrix::matrix() {}

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
    copy_from(other);
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
 * 3. Складываем произведения алг. элементов и алг. доп. к ним
 * 4. Возвращаем определитель
 */
double matrix::determinant()
{
    if (rows != cols) // не квадратная матрица
        throw std::logic_error("Non square matrix");
    if (rows == 2) // частный случай
        return elems[0] * elems[3] - elems[1] * elems[2];

    double result = 0.0;
    for (int i = 0; i < cols; ++i)
    {
        result += get_alg_com(0, i) * elems[i];
    }
    return result;
}

matrix matrix::transposition()
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

matrix matrix::get_inverse()
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

void matrix::export_to_scv(const std::string &filename)
{
    std::ofstream fout(filename + ".scv");
    std::string prev_delim = print_delim;
    if (fout.is_open())
    {
        print_delim = ", ";
        (*this) >> fout;
        print_delim = prev_delim;
    }
    fout.close();
}


matrix matrix::operator*(matrix &other)
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
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            vec.push_back(get(i, j) * num);
        }
    }
    return matrix(vec, rows, cols);
}

void matrix::operator>>(std::ostream &out)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            out << std::fixed
                << std::setw(print_width)
                << std::setprecision(print_prec)
                << get(i, j) << print_delim;
        }
        if (i < rows - 1)
            out << '\n';
    }
    out << std::flush;
}

void matrix::operator>>(const std::string &output_filename)
{
    std::ofstream fout(output_filename);
    if (fout.is_open())
    {
        (*this) >> fout;
    }
    fout.close();
}

matrix matrix::operator^(int pow)
{
    if (pow == -1)
        return transposition();
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
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            get(i, j) *= num;
        }
    }
}

void matrix::operator*=(matrix &other)
{
    matrix temp(*this);
    *this = temp * this;
}

void matrix::operator*=(matrix *other)
{
    (*this) *= (*other);
}

void matrix::operator=(const matrix &other)
{
    copy_from(other);
}

matrix::row &matrix::operator[](int row)
{
    rp.row_num = row;
    return rp;
}


int matrix::get_cols()
{
    return cols;
}

int matrix::get_rows()
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
}

double matrix::get_alg_com(int row, int col)
{
    if (get(row, col) == 0)
        return 0;

    static std::vector<matrix *> minors;
    if (minors.size() < rows - 2)
    {
        static int high_order = 2;
        while(high_order < rows)
        {
            minors.push_back(new matrix(high_order, high_order));
            high_order++;
        }
    }

    matrix minor = get_minor(row, col, minors);
    double result = minor.determinant();
    if ((row + col) % 2 != 0)
        result = -result;

    return result;
}

matrix &matrix::get_minor(
    int row, int col, std::vector<matrix *> minors
) {
    matrix &minor = *(minors[rows - 3]);
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

double &matrix::get(int row, int col)
{
    return elems[row * cols + col];
}

void matrix::copy_from(const matrix &other)
{
    this->cols = other.cols;
    this->rows = other.rows;
    this->elems = other.elems;
    this->print_prec = other.print_prec;
    this->print_width = other.print_width;
    this->print_delim = other.print_delim;
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

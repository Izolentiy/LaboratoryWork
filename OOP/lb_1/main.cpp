#include "str_helper.h"
#include "matrix.h"
#include "complex/complex.h"

void scenario_3();
void scenario_4();
void interpreter_test();
void determinant_test();
void task();
void complex_equations_system();

int main()
{
    // task();
    complex_equations_system();
}

void complex_equations_system() {
    matrix<complex> a("..\\input\\complex_A.txt");
    matrix<complex> b("..\\input\\complex_B.txt");
    matrix<complex> x;
    
    std::cout << "A\n";
    std::cout << a << "\n\n";

    std::cout << "det A:\n";
    std::cout << a.determinant() << "\n\n";

    std::cout << "A^-1\n";
    std::cout << (a ^ -1) << "\n\n";

    std::cout << "B\n";
    std::cout << b << "\n\n";

    std::cout << "A^-1 * A\n";
    std::cout << (a ^ -1) * a << "\n\n";

    x = (a ^ -1) * b;
    std::cout << "X = A^-1 * B\n";
    std::cout << x;
}

void interpreter_test()
{   
    std::cout << "\n\nINTERPRETER TESTS\n\n";
    using str_helper::compare;
    using str_helper::print_diff;
    struct interpreter_test_case
    {
        std::string filename;
        int expected_rows;
        int expected_cols;
        bool expected_invalid;
    };
    std::vector<interpreter_test_case> test_cases = {
        {"just_minus_among_nums.txt", 0, 0, true},
        {"missing_num_in_row.txt", 0, 0, true},
        {"extra_num_in_row.txt", 0, 0, true},
        {"different_delims.txt", 2, 3, true},
        {"extra_spaces.txt", 4, 5, true},
        {"empty_file.txt", 0, 0, true},
        {"negative_nums.txt", 3, 3, false},
        {"decimal_nums.txt", 2, 3, false},
        {"matrix_1x1.txt", 1, 1, false},
        {"matrix_1x3.txt", 1, 3, false},
        {"matrix_2x2.txt", 2, 2, false},
        {"matrix_3x1.txt", 3, 1, false},
        {"matrix_4x5.txt", 4, 5, false},
    };
    for (interpreter_test_case &t : test_cases)
    {
        bool valid_match = true;
        bool cols_match = true;
        bool rows_match = true;
        std::string status = FAILURE;
        std::string filename;
        matrix<double> m;
        try
        {
            filename = "test_cases\\" + t.filename;
            m = matrix<double>(filename);
            if (t.expected_invalid)
                valid_match = false;
            if (m.get_cols() != t.expected_cols)
                cols_match = false;
            if (m.get_rows() != t.expected_rows)
                rows_match = false;
        }
        catch(const std::exception& e)
        {
            if (compare(e.what(), UNABLE_TO_OPEN_FILE))
                std::cerr << e.what() << " : " << filename << '\n';
            if (compare(e.what(), INVALID_INPUT) && !t.expected_invalid)
                valid_match = false;
        }
        if (valid_match && cols_match && rows_match)
            status = PASS;
        std::cout << t.filename << "   " << status << '\n';

        if (!cols_match)
            print_diff("COLS", t.expected_cols, m.get_cols());
        if (!rows_match)
            print_diff("ROWS", t.expected_rows, m.get_rows());
        if (!valid_match)
            print_diff("INVALID", t.expected_invalid, !t.expected_invalid);
    }
}

void determinant_test() {
    struct det_test_case
    {
        std::string filename;
        double expected;
    };
    std::vector<det_test_case> test_cases = {
        {"matrix_1x1.txt", 2},
        {"matrix_2x2.txt", -62},
        {"matrix_7x7.txt", 2},
        {"matrix_1x3.txt", nan("")},
        {"zero_det.txt", 0},
    };
    for (det_test_case &t : test_cases)
    {

    }
}

void task()
{
    try
    {
        matrix<double> a("..\\input\\matrix-A.txt");
        matrix<double> b("..\\input\\matrix-B.txt");
        matrix<double> x;

        std::cout << "A\n";
        std::cout << a << "\n\n";

        std::cout << "A^-1\n";
        std::cout << (a ^ -1) << "\n\n";

        std::cout << "B\n";
        std::cout << b << "\n\n";

        std::cout << "A^-1 * A\n";
        std::cout << (a ^ -1) * a << "\n\n";

        x = (a ^ -1) * b;
        std::cout << "X = A^-1 * B\n";
        std::cout << x;

        "output\\x.txt" << x;
        x.export_to_csv("output\\x.csv");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void scenario_4()
{
    try
    {
        matrix<double> d("input\\matrix_D.txt");
        matrix<double> a("input\\matrix_A.txt");
        std::cout << " ~~~ A and D created\n\n";

        matrix<double> c = d; // copy constructor
        std::cout << " ~~~ C copied from D\n\n";
        std::cout << c[0][0] << " " << d[0][0] << std::endl;
        c[0][0] = 1;
        std::cout << c[0][0] << " " << d[0][0] << std::endl;

        a = d; // assignment operator
        std::cout << " ~~~ D assigned to A\n\n";
        std::cout << a[0][0] << " " << d[0][0] << std::endl;
        a[0][0] = 1;
        std::cout << a[0][0] << " " << d[0][0] << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void scenario_3()
{
    try
    {
        matrix<double> d("input\\matrix_D.txt");
        matrix<double> a("input\\matrix_A.txt");
        double det_d = 0, det_a = 0;
        det_d = d.determinant();
        det_a = a.determinant();
        std::cout << a << "\n\n";
        "output\\scenario_3.txt" << a;

        matrix<double> t = d ^ (-1); // inverse
        std::cout << t << "\n\n";
        t.export_to_csv("kek");

        matrix<double> k = d ^ 2;
        std::cout << k << "\n\n";

        "output\\scenario_3.txt" << k;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
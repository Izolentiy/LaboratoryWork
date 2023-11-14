#include "str_helper.h"
#include "time_helper.hpp"
#include "matrix.h"

void scenario_1();
void scenario_2();
void scenario_3();
void scenario_4();
void double_converter_test();
void interpreter_test();
void determinant_test();
void task();

int main()
{
    // scenario_1();
    // scenario_2();
    // scenario_3();
    // scenario_4();
    // task();
    double_converter_test();
    interpreter_test();
}

void double_converter_test()
{
    struct text_test_case
    {
        std::string name;
        std::string given;
        double expected;
    };
    std::vector<text_test_case> test_cases = {
        {"integer_negative", "-42", -42},
        {"decimal_negative", "-42.234", -42.234},
        {"whitespace", " ", nan("")},
        {"just_minus", "-", nan("")},
        {"starts_with_dot", ".234", nan("")},
        {"ends_with_dot", "42.", nan("")},
        {"too_many_dots", "4..23", nan("")},
        {"one_digit_positive", "3", 3},
        {"one_digit_negative", "-3", -3},
        {"too_many_minuses", "-4-2.23", nan("")},
        {"some_random_number", "10101.402", 10101.402},
    };
    for (text_test_case &t : test_cases)
    {
        std::string status;
        double result;
        try
        {
            result = str_helper::to_double(t.given);
        }
        catch (const std::exception &e)
        {
            result = nan("");
        }

        // both are NaN
        if (t.expected != t.expected && result != result)
            status = PASS;
        // both are equal
        else if (t.expected == result)
            status = PASS;
        else
            status = FAILURE;

        std::cout << t.name << "   " << status << '\n';
        if (status == FAILURE)
            str_helper::print_diff("", t.expected, result); 
    }
}

void interpreter_test()
{
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
        {"extra_spaces.txt", 4, 5, true},
        {"empty_file.txt", 0, 0, true},
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
        matrix m;
        try
        {
            filename = "test_cases\\" + t.filename;
            m = matrix(filename);
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
        matrix a("input\\matrix-A.txt");
        matrix b("input\\matrix-B.txt");
        matrix x;

        std::cout << "A\n";
        std::cout << a << "\n\n";

        std::cout << "A^(-1)\n";
        std::cout << (a ^ -1) << "\n\n";

        std::cout << "B\n";
        std::cout << b << "\n\n";

        std::cout << "Test\n";
        std::cout << (a ^ -1) * a << "\n\n";

        x = (a ^ -1) * b;
        std::cout << "X\n";
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
        matrix d("input\\matrix_D.txt");
        matrix a("input\\matrix_A.txt");
        std::cout << " ~~~ A and D created\n\n";

        matrix c = d; // copy constructor
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
        matrix d("input\\matrix_D.txt");
        matrix a("input\\matrix_A.txt");
        double det_d = 0, det_a = 0;
        det_d = d.determinant();
        det_a = a.determinant();
        std::cout << a << "\n\n";
        "output\\scenario_3.txt" << a;

        matrix t = d ^ (-1); // inverse
        std::cout << t << "\n\n";
        t.export_to_csv("kek");

        matrix k = d ^ 2;
        std::cout << k << "\n\n";

        "output\\scenario_3.txt" << k;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void scenario_2()
{
    try
    {
        matrix a = matrix("input\\matrix_A.txt");
        double det = 0.0;

        auto action = [&]()
        {
            det = a.determinant();
        };
        run_with_time_measurement(action, time_unit::micros);

        a.set_print_precision(0);
        a.set_print_width(2);
        std::cout << "\nmatrix A("
                  << a.get_rows() << ", " << a.get_cols()
                  << ") \ndet: " << det << "\n\n";
        std::cout << a;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void scenario_1()
{
    // std::ifstream fin;
    // try
    // {
    //     matrix &a = *(read(fin, "input\\matrix_A.txt"));
    //     std::cout << "\nmatrix A" << std::endl;
    //     a.print_elements();

    //     matrix *a9 = a * 9;
    //     std::cout << "\nmatrix 9 * A" << std::endl;
    //     a9->print_elements();

    //     std::cout << "\nmatrix A: e[0][0] = " << a[0][0] << std::endl;

    //     matrix *c = a.get_inverse();
    //     std::cout << "\nmatrix A inverse" << std::endl;
    //     c->print_elements();

    //     matrix *d = a * c;
    //     std::cout << "\nmatrix A * inverse A" << std::endl;
    //     d->print_elements();

    //     matrix *b = a.transposition();
    //     std::cout << "\nmatrix A transpositioned" << std::endl;
    //     b->print_elements();

    //     delete b;
    //     delete d;
    //     delete c;
    //     delete a9;
    //     std::cout << "Deleted objects" << std::endl;

    //     matrix &p = *(read(fin, "input\\matrix_B.txt"));
    //     matrix &q = *(read(fin, "input\\matrix_C.txt"));

    //     std::cout << "\nmatrix P" << std::endl;
    //     p.print_elements();

    //     std::cout << "\nmatrix Q" << std::endl;
    //     q.print_elements();

    //     std::cout << "\nmatrix P * Q" << std::endl;
    //     matrix *j = p * q;
    //     j->print_elements();

    //     std::cout << "\nmatrix Q * P" << std::endl;
    //     matrix *i = q * p;
    //     i->print_elements();

    //     delete i;
    //     delete j;
    //     delete &q;
    //     delete &p;
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
}
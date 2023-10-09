#include "str_helper.h"
#include "time_helper.hpp"
#include "matrix.h"

void scenario_1();
void scenario_2();
void scenario_3();

int main()
{
    // scenario_1();
    // scenario_2();
    scenario_3();
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
        a >> std::cout;
        a >> "output\\scenario_3.txt";
        std::cout << "\n\n";
        
        matrix t = d^(-1); // transpositioned
        t >> std::cout;
        t.export_to_scv("kek");
        std::cout << "\n\n";

        matrix k = d^2;
        k >> std::cout;
        std::cout << "\n\n";

    }
    catch(const std::exception& e)
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
        // run_with_time_measurement(action, time_unit::millis);
        run_with_time_measurement(action, time_unit::micros);
        // run_with_time_measurement(action, time_unit::nanos);

        a.set_print_precision(0);
        a.set_print_width(2);
        std::cout << "\nmatrix A("
                  << a.get_rows() << ", " << a.get_cols()
                  << ") det: " << det << "\n";
        a >> std::cout;
    }
    catch(const std::exception& e)
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
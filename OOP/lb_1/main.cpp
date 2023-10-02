#include "str_helper.h"
#include "matrix.h"
#include "time_helper.hpp"

void str_helper_test();
void scenario_1();
void scenario_2();

int main()
{
    scenario_2();
}

void scenario_2()
{
    std::ifstream fin("input.txt");
    if (fin.is_open()) try
    {
        matrix a = matrix(fin);
        double det = 0.0;
        // Measuring determinant calculation time
        auto action = [&]()
        {
            det = a.determinant();
        };

        run_with_time_measurement(action, time_unit::millis);
        // run_with_time_measurement(action, time_unit::micros);
        // run_with_time_measurement(action, time_unit::nanos);

        a.set_print_precision(0);
        a.set_print_width(2);
        a.print_elements();
        std::cout << "\nmatrix A("
                  << a.get_rows() << ", " << a.get_cols()
                  << ") det: " << det << std::endl;
    }
    catch (const char *msg)
    {
        std::cout << msg << std::endl;
    }
    fin.close();
}

void scenario_1()
{
    std::ifstream fin("input.txt");
    if (fin.is_open()) try
    {
        matrix a(fin);
        std::cout << "\nmatrix A" << std::endl;
        a.print_elements();

        matrix *a9 = a * 9;
        std::cout << "\nmatrix 9 * A" << std::endl;
        a9->print_elements();

        std::cout << "\nmatrix A: e[0][0] = " << a[0][0] << std::endl;

        matrix *c = a.get_inverse();
        std::cout << "\nmatrix A inverse" << std::endl;
        c->print_elements();

        matrix *d = a * c;
        std::cout << "\nmatrix A * inverse A" << std::endl;
        d->print_elements();

        matrix *b = a.transposition();
        std::cout << "\nmatrix A transpositioned" << std::endl;
        b->print_elements();
        
        delete b;
        delete d;
        delete c;
        delete a9;
        std::cout << "Deleted objects" << std::endl;
    }
    catch (const char *msg)
    {
        std::cout << msg << std::endl;
    }
    fin.close();
}

void str_helper_test()
{
    std::ifstream fin("input.txt");
    if (fin.is_open())
        try
        {
            std::vector elements = str_helper::to_vector(fin);
            std::cout << std::fixed << std::setprecision(0);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    std::cout << elements[i * 4 + j] << " ";
                }
                std::cout << "\n";
            }

            double result = str_helper::to_double("1234,56789");
            std::cout << "Result: " << result << std::endl;
        }
        catch (char const *msg)
        {
            std::cout << msg << std::endl;
        }
    fin.close();
}
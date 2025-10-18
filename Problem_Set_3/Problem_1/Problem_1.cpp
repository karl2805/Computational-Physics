#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>

#define PI 3.14159265359
#define LINEBREAK std::cout << "------------------------------------------------------------------\n";

template<typename T>void printElement(T t)
{
    std::cout << std::left << std::setw(20) << std::setfill(' ') << t;
}
//central differentiate function
double CD(double x, double dx, double (*InputFunction)(double))
{
    return (InputFunction(x + dx) - InputFunction(x - dx)) / (2 * dx);
}

double BisectionMethod(double (*F)(double), double x_a, double x_b, int iterations=10)
{
   

    if(F(x_a)*F(x_b) > 0)
    {
        return 0;
    }
        

    double x_l = x_a, x_u = x_b, x_m, product;

    for (int i = 0; i < iterations; i++)
    {
        x_m = (x_l + x_u) / 2;

        product = F(x_l) * F(x_m);

        if (product < 0)
        {
            x_u = x_m;
            continue;
        }

        if (product > 0)
        {
            x_l = x_m;
            continue;
        }

        if (product == 0)
        {
           return x_m;
        }
    }

    return x_m;

}
double SecantMethod(double (*F)(double), double x_i, double x_i_1, int iterations=10)
{
    double xi = x_i, xi1 = x_i_1, next = 0;

    for (int i = 0; i < iterations; i++)
    {
        next = xi - (F(xi) * (xi - xi1)) / (F(xi) - F(xi1));

        //prevents double running out of accuracy
        if ((next - xi) / next < 0.0000001)
            return next;

        xi1 = xi;

        xi = next;
    }

    return next;

    
}
double NewtonRaphsonMethod(double (*F)(double), double x_i, int iterations=10)
{
    double temp = 0;
    for (int i = 0; i < iterations; i++)
    {
        temp = x_i;
        x_i = temp - (F(temp)) / CD(temp, 0.01, F);
    }

    return x_i; 

    
}

double F(double x)
{
    return cos(x) - 0.25;
}



int main()
{
    std::vector<double> bisect_data, secant_data, newtonrapson_data;
    double true_error, rel_error, e_0;

    LINEBREAK;
    std::cout << "Bisection Method" << std::endl;
    LINEBREAK;
    
    printElement("Iteration");
    printElement("Abs_True_Error");
    printElement("Abs_Approx_Error");
    std::cout << "\n\n";

    double exact = 1.31811607165;
   
    for (int i = 0; i <= 21; i++)
    {
        true_error = std::abs(BisectionMethod(F, 0, PI/2, i) - exact);
        rel_error = std::abs(BisectionMethod(F, 0, PI/2, i) - exact) / exact;
        e_0 = std::abs(BisectionMethod(F, 0, PI/2, 0) - exact);

        printElement(i);
        printElement(true_error);
        printElement(rel_error);

        std::cout << std::endl;

        bisect_data.push_back(std::abs(true_error / e_0));
        
    }

    

    std::cout << '\n';
    LINEBREAK;
    std::cout << "Secant Method" << std::endl;
    LINEBREAK;

    printElement("Iteration");
    printElement("Abs_True_Error");
    printElement("Abs_Approx_Error");
    std::cout << "\n\n";

    for (int i = 0; i <= 21; i++)
    {
        true_error = std::abs(SecantMethod(F, 0, PI/2, i) - exact);
        rel_error = std::abs(SecantMethod(F, 0, PI/2, i) - exact) / exact;
        e_0 = std::abs(SecantMethod(F, 0, PI/2, 0) - exact);

        printElement(i);
        printElement(true_error);
        printElement(rel_error);
        std::cout << std::endl;

        secant_data.push_back(std::abs(true_error / e_0));
        
    }
    std::cout << '\n';
    LINEBREAK;
    std::cout << "Newton Rapson Method" << std::endl;
    LINEBREAK;

    printElement("Iteration");
    printElement("Abs_True_Error");
    printElement("Abs_Relative_True_Error");
    std::cout << "\n\n";

    for (int i = 0; i <= 21; i++)
    {
        true_error = std::abs(NewtonRaphsonMethod(F, PI/2, i) - exact);
        rel_error = std::abs(NewtonRaphsonMethod(F, PI/2, i) - exact) / exact;
        e_0 = std::abs(NewtonRaphsonMethod(F, PI/2, 0) - exact);

        printElement(i);
        printElement(true_error);
        printElement(rel_error);
        std::cout << std::endl;

        newtonrapson_data.push_back(std::abs(true_error / e_0));
    }

    std::ofstream output("data.csv");
    
    output << "index" << ',' << "bisect" << ',' << "secant" << ',' << "newtonrapson" << std::endl;
    for (int i = 0; i <= 21; i++)
    {
        output << i << ',' << bisect_data.at(i) << ',' << secant_data.at(i) << ',' << newtonrapson_data.at(i) << std::endl;
    }
  
}
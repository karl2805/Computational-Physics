#include <iostream>
#include <cmath>

double BisectionMethod(double (*F)(double), double x_a, double x_b, int iterations=10)
{
    if(F(x_a)*F(x_b) > 0)
    {
        return 0;
    }
        
    double x_l = x_a, x_u = x_b, x_m, product;

    for (int i = 0; i <= iterations; i++)
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

double SimponsRule(double (*F)(double), double a, double b, double n)
{
    double odd_sum = 0, even_sum = 0;

    double h = (b-a) / n;

    double x_i;

    //odd sum
    for (int i = 1; i <= n - 1; i += 2)
    {
        x_i = a + i*h;
        odd_sum += F(x_i);
    }

    //even sum
    for (int i = 2; i <= n - 2; i += 2)
    {
        x_i = a + i*h;
        even_sum += F(x_i);
    }

    return ((b-a)/(3*n)) * (F(a) + 4*odd_sum + 2*even_sum + F(b));
}
 


double F(double x)
{
    return -std::pow(x, 4) + 7*std::pow(x, 3) - 5*std::pow(x, 2) + 15;
}

int main()
{
    //find left root. From graph, good points are -0.5, -1.5  and 6, 7
    double left_root  = BisectionMethod(F, -1.5, -0.5, 150);
    double right_root =  BisectionMethod(F, 6, 7, 150);

    std::cout << "left root: " << left_root << std::endl << "right root: " << right_root << std::endl;

    std::cout << "Integral between the two roots: " << SimponsRule(F, left_root, right_root, 100);
}
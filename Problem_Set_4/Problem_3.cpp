#include <iostream>
#include <cstdlib> 
#include <stdlib.h>
#include <time.h> 
#include <cmath>
#include <fstream>
#include <random>

std::random_device rd;
std::default_random_engine generator(rd()); // rd() provides a random seed
std::uniform_real_distribution<double> distribution(0,10);

double number = distribution(generator);

double F(double x)
{
    return (300*x) / (1 + std::exp(x));
}

 double TrapesiumIntegrate(double (*F)(double), double lower_bound, double upper_bound, double n, bool return_step_size)
    {
        double h = (upper_bound - lower_bound) / (n);

        double summation = 0;

        for (int i = 0; i < n; i++)
        {
            summation += F((lower_bound) + (i * h));
        }

        if(return_step_size)
            return h;

        return (0.5 * h)*(F(lower_bound) + (2 * summation) + F(upper_bound));
    }

int main ()
{
    std::srand(time(0));

    double a = 0;
    double b = 10;
    double true_value = 246.590293505238;

    int iterations = 1000000;

   
     double sum = 0;
     for (int i = 0; i < iterations; i++)
     {
         double x = distribution(generator);
         sum += F(x);
     }

     std::cout << "Integral Value: " << (sum * (b-a)) / iterations << std::endl;
    


    for (int num_points = 0; num_points < 1000000; num_points++)
    {
        double sum = 0;

        for (int i = 0; i < num_points; i++)
        {
            double x = distribution(generator);

            sum += F(x);
        }
        double approx = (sum * (b-a)) / num_points;

        double percent_error = (std::abs(true_value - approx) / true_value) * 100;

        if (percent_error < 0.01)
        {
            std::cout << "Number of points necessary for error less than 0.01%: " << num_points << " points" << std::endl;
            break;
        }
    }

    

    for (double n = 1; n < 10000; n++)
    {   
        double approx = TrapesiumIntegrate(F, 0, 10, n, false);

        double percent_error = (std::abs(true_value - approx) / true_value) * 100;

        if (percent_error < 0.01)
        {
            std::cout << "Step size needed for trapezium rule error less than 0.01%: " << TrapesiumIntegrate(F, 0, 10, n, true) << std::endl; 
            break;
        }
    }

    
}

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

int main ()
{
    std::srand(time(0));

    double a = 0;
    double b = 10;
    double true_value = 246.590293505238;

   
     double sum = 0;
     for (int i = 0; i < 100000; i++)
     {
         double x = distribution(generator);
         sum += F(x);
     }

     std::cout << "Integral Approximate Value: " << (sum * (b-a)) / 100000 << std::endl;
    


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
    std::cout << "This number will always be different due to the randomness of this technique" << "\n";
}

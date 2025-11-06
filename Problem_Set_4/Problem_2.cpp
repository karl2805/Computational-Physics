#include <iostream>
#include <cstdlib> 
#include <stdlib.h>
#include <time.h> 
#include <cmath>
#include <fstream>
#include <random>

#define PI 3.1415926535897932384626433

std::random_device rd;
std::default_random_engine generator(rd()); //providing a random seed
std::uniform_real_distribution<double> distribution(0,1);

int main()

{

    double pi_estimate;
    std::ofstream outputfile("pierror.csv");

    double counter = 0;
    double x, y;

    for (int i = 0; i < 1000000; i++)
        {
            x = distribution(generator);
            y = distribution(generator);

            if (std::sqrt((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5)) < 0.5)
                counter++;
        }   

    pi_estimate = 4 * (counter / 1000000);

    std::cout << "Estimation of PI: " << pi_estimate << std::endl;


    for (int iterations = 1; iterations < 4050; iterations++)
    {
        counter = 0;

        std::default_random_engine generator;

        for (int i = 0; i < iterations; i++)
        {
            x = distribution(generator);
            y = distribution(generator);

            if (std::sqrt((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5)) < 0.5)
                counter++;
        }   

        pi_estimate = 4 * (counter / iterations);

        double percent_error = (std::abs(pi_estimate - PI) / PI) * 100;

        outputfile << iterations << "," << percent_error << "\n";
    }

    




}
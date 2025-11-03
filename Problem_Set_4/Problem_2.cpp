#include <iostream>
#include <cstdlib> 
#include <stdlib.h>
#include <time.h> 
#include <cmath>
#include <fstream>

#define PI 3.1415926535897932384626433


int main()
{
    std::ofstream outputfile("pierror.csv");

    for (int iterations = 1; iterations < 2000; iterations++)
    {
        double counter = 0;

        double x, y;


        std::srand(time(0));

        for (int i = 0; i < iterations; i++)
        {
            x = (double) std::rand() / RAND_MAX;
            y = (double) std::rand() / RAND_MAX;

            if (std::sqrt(x*x + y*y) < 1)
                counter++;

        }   

        double pi_estimate = 4 * (counter / iterations);

        

        double percent_error = (std::abs(pi_estimate - PI) / PI) * 100;

        outputfile << iterations << "," << percent_error << "\n";
    }


}
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#define LINEBREAK std::cout << "------------------------------------------------------------------\n\n";



int main ()
{   
    std::cout << "Part (a):\n";
    std::cout << "First Approxation sin(x) = x: \n";
    double exact = 0, approx = 0, error = 0, x = 0;

    for (x = 0.0001; x <= 3; x += 0.0001)
    {
        exact = std::sin(x);
        error = (std::abs(exact - x)) / exact;

        if (error >= 0.01)
            break;
    }

    std::cout << "First angle with error greater than 1%: " << x * (180/M_PI) << " degrees\n";

    LINEBREAK;

    approx = x - ((std::pow(x, 3)) / 6);
    error = (std::abs(exact - approx) / exact);

    std::cout << "Part (b):\n";
    std::cout << "Error with second term at angle " << x * (180/M_PI) << " degrees" << " = " << error * 100 << "%\n";

    LINEBREAK;

    for (x = 0.0001; x <= 3; x += 0.0001)
    {
        exact = std::sin(x);
        approx = x - ((std::pow(x, 3)) / 6);

        error = (std::abs(exact - approx)) / exact;

        if (error >= 0.01)
            break;
    }

    std::cout << "Part (c):\n";
    std::cout << "First angle with error greater than 1%: "<< x * (180/M_PI) << " degrees\n";
    LINEBREAK;
   



}
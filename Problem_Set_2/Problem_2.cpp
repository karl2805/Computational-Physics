#include <iostream>
#include <iomanip>

#define LINEBREAK std::cout << "------------------------------------------------------------------\n";

double f(double x)
{
    return x*x - x + 1;
}

double CentralDifferentiate(double x, double dx, double (*InputFunction)(double))
{
    return (InputFunction(x + dx) - InputFunction(x - dx)) / (2 * dx);
}

int main()
{   
    LINEBREAK;
    std::cout << "Derivative approximation f'(2) with varying step size del_x: \n";

    LINEBREAK;

    std::cout << std::left << "del_x" << "\t" << "f'(2)" << '\t' << "Abs true error" << std::endl;

    double dir = CentralDifferentiate(2, 0.25, f);
    
    std::cout << std::left << 0.25 << '\t' << dir << '\t' << std::abs(3 - dir) / 3 << std::endl;

    dir = CentralDifferentiate(2, 0.125, f);

    std::cout << std::left << 0.125 << '\t' << dir << '\t' << std::abs(3 - dir) / 3 << std::endl;

    LINEBREAK;
    std::cout << "The Abs true error will always be zero no matter how large del_x is:\n";
    LINEBREAK;

    std::cout << std::left << "del_x" << "\t" << "f'(2)" << '\t' << "Abs true error" << std::endl;

    for (double i = 2; i <= 10; i += 2)
    {
        dir = CentralDifferentiate(2, i, f);
        
        std::cout << std::left << i << '\t' << dir << '\t' << std::abs(3 - dir) / 3 << std::endl;
    }

    LINEBREAK;
    std::cout << "Explained in canvas submission\n";
    LINEBREAK;

}

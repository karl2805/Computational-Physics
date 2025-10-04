#include <iostream>

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
    std::cout << CentralDifferentiate(2, 5, f) << std::endl;
    
    
}

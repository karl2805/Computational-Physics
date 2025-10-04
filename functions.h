#pragma once

#define LINEBREAK std::cout << "------------------------------------------------------------------\n";

#define LINEBREAK_RETURN std::cout << "------------------------------------------------------------------\n\n";

double CentralDifferentiate(double x, double dx, double (*InputFunction)(double))
{
    return (InputFunction(x + dx) - InputFunction(x - dx)) / (2 * dx);
}

double IntegrateTrap(double (*F)(double), double lower_bound, double upper_bound, double n)
{
    double h = (upper_bound - lower_bound) / (n);

    double summation = 0;

    for (int i = 0; i < n; i++)
    {
        summation += F((lower_bound) + (i * h));
    }

    return (0.5 * h)*(F(lower_bound) + (2 * summation) + F(upper_bound));
}

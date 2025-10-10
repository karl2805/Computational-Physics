    #include <iomanip>
    #include <iostream>
    #include <cmath>

    double Integrate(double (*F)(double), double lower_bound, double upper_bound, double n)
    {
        double h = (upper_bound - lower_bound) / (n);

        double summation = 0;

        for (int i = 0; i < n; i++)
        {
            summation += F((lower_bound) + (i * h));
        }

        return (0.5 * h)*(F(lower_bound) + (2 * summation) + F(upper_bound));
    }

    double F(double x)
    {
        return (300*x)/(1 + std::exp(x));
    }

    int main()
    {
        std::cout << std::setprecision(4);
        double true_value = 246.590293505238;

        
        std::cout << "Approximation of Integral of f(x) from 0 to 10 with n segments: \n";

        std::cout << "n" << '\t' << "Approx. Integral" << '\t' << "% True Error\n\n"; 

        for (int n = 2; n <= 64; n *= 2)
        {   
            double approx = Integrate(F, 0, 10, n);
            std::cout << n << '\t' << approx << std::setw(25) << (std::abs(true_value - approx) / true_value) * 100 << " %\n";
        }
    }

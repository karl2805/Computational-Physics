#include <iostream>

double CentralDifferentiate(double x, double dx, double (*InputFunction)(double))
{
    return (InputFunction(x + dx) - InputFunction(x - dx)) / (2 * dx);
}

double ForwardDifferentiate(double x, double dx, double (*InputFunction)(double))
{
    return (InputFunction(x + dx) - InputFunction(x)) / dx;
}

double BackwardDifferentiate(double x, double dx, double (*InputFunction)(double))
{
    return (InputFunction(x) - InputFunction(x - dx)) / dx;
} 

double F(double x)
{
    return x*x*x - 3*x*x + 3;
}


int main()
{
    double x = 0;
    double dx = 0.1;
    std::cout << "Enter x: ";
    std::cin >> x;

    double central_derivative = CentralDifferentiate(x, dx, F);

    std::cout << "Central Derivate at x approximation = " << CentralDifferentiate(x, dx, F) << std::endl;
    
    //The true error will always be (dx)^2 as the triple derivate of the input function is 6. Derived in photo of copy.

    double central_error = dx * dx;

    std::cout << "Error in central differentitation = " << central_error << std::endl << "\n";

    double forward_differentiate = ForwardDifferentiate(x, dx, F);

    std::cout << "Forward Derivate at x approximation = " << forward_differentiate << std::endl;

    //the true derivative is the central_derivative - central_error

    double forward_derivate_error = std::abs((central_derivative - central_error) - forward_differentiate);

    std::cout << "Error in Forward differentitation = " << forward_derivate_error << std::endl << "\n";



    double back_differentiate = BackwardDifferentiate(x, dx, F);

    std::cout << "Backward Derivate at x approximation = " << back_differentiate << std::endl;

    double back_derivate_error = std::abs((central_derivative - central_error) - back_differentiate);

    std::cout << "Error in Backward differentitation = " <<  back_derivate_error << std::endl << "\n";



    
    while (forward_derivate_error >= central_error)
    {
        forward_differentiate = ForwardDifferentiate(x, dx, F);

        forward_derivate_error = std::abs((central_derivative - central_error) - forward_differentiate);

        dx = dx - 0.0001;

        if(dx < 0)
            break;
    }

    std::cout << "Step size needed for forward differentiation error to be less than central differentiation error: " << dx << std::endl;





}
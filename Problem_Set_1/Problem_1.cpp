#include <iostream>

void inputManager(double& x, std::string message)
{
    std::cout << message;
    std::cin >> x;
    
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        
        std::cout << "That's not a number try again!" << std::endl;
        std::cout << message;

        std::cin >> x;

    }
}

int main()
{
    double a, b, c;

    inputManager(a, "Enter the first number: ");
    inputManager(b, "Enter the second number: ");
    inputManager(c, "Enter the third number: ");
    
    std::cout << '\n' << "Sum of the numbers: " << a + b + c << '\n';
    std::cout << "Product of the numbers: " << a * b * c << '\n';

}
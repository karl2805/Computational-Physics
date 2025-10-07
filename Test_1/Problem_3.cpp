#include <iostream>

int main()
{
    double n = 0;
    std::cout << "Enter number: ";
    std::cin >> n;

    if (n == 0)
    {
        std::cout << "The factorial of your number is: 1" << std::endl;
        return 0;
    }

    for (int i = n-1; i > 0; i--)
    {
        n *= i;
    }

    std::cout << "The factorial of your number is: " << n << std::endl;
}
#include <iostream>

int main()
{
    double a, b = 0;
    std::cout << "Enter the first number: " << std::endl;
    std::cin >> a;

    std::cout << "Enter the second number: " << std::endl;
    std::cin >> b;

    if(a > b)
        std::cout << "The larger number is: " << a << std::endl;


    if(b > a)
        std::cout << "The larger number is: " << b << std::endl;
    

    else
        std::cout << "The numbers are equal" << std::endl;
}
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    double input;
    
    std::cout << "Decimal to Binary Converter \n";

    std::cout << "Enter a decimal number: ";
    std::cin >> input;

    //input error detection
    if (!input || input < 0)
    {
        while (!input || input < 0)
        {
            std::cin.clear();
            std::cin.ignore(100, '\n');

            std::cout << "Input must be a positive number! ";
            std::cout << "Try again: ";
            std::cin >> input;
        }
    }


    //cast to integer to process digits before decimal point
    int int_input = int(input);

    int i = -1;
    int r = -1;

    std::vector<int> before_decimal;

    //convert to binary before the decimal point
    while (i != 0)
    {
        i = int_input / 2;
        r = int_input % 2;

        //inset binary backwards into array
        before_decimal.insert(before_decimal.begin(), r);

        int_input = i;
    }

    //get the decimal part of the input
    double after_decimal_input = input - floor(input);

    std::vector<int> after_decimal;

    double j = -1.0;


    while (after_decimal_input != 0.0)
    {
        j = after_decimal_input * 2;

        after_decimal.push_back(floor(j));

        after_decimal_input = j - floor(j);
    }

    std::cout << "Your number in binary: ";


    for (int i : before_decimal)
    {
        std::cout << i;
    }

    //don't display decimal point if input does not contain a decimal point
    if (after_decimal.size() > 0)
    {
        std::cout << '.';

        for (int i : after_decimal)
        {
            std::cout << i;
        }
    }
	std::cout << std::endl;
}

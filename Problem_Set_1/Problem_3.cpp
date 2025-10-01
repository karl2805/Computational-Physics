#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>

int validateBinaryNumber(std::string input)
{
    int decimal_counter = 0;
    for (char c : input)
    {
        if(c != '0' && c != '1')
        {
            if(c == '.' && decimal_counter < 1)
                decimal_counter++;
            else
                return -1;
        }
    }

    return 0;
}

int main()
{
    std::string binary_input;

    std::cout << "Enter binary number:  ";
    std::cin >> binary_input;

    
    
    while (validateBinaryNumber(binary_input) == -1)
    {
        std::cout << "That's not a binary number, try again: ";
       
        std::cin >> binary_input;
    }




    int decimal_point_index;

    if (binary_input.find_first_of('.') != -1)
    {
        decimal_point_index = binary_input.find_first_of('.');
    }

    else 
    {
        decimal_point_index = binary_input.length();
    }

    float decimal_buffer = 0;

    //add powers of 2 from before decimal place
    for (int i = decimal_point_index - 1; i >= 0; i--)
    {
        decimal_buffer += (pow(2, abs(i - (decimal_point_index - 1))) * ((int)binary_input.at(i) - 48));
    }
    
    //handle digits after decimal point only if there is a decimal point in the input
    int j = -1;

    if (binary_input.find_first_of('.') != 0)
    {
        for (int i = decimal_point_index + 1; i < binary_input.size(); i++)
        {
            decimal_buffer += (pow(2, j)) * ((int)binary_input.at(i) - 48);
            j--;
        }
    }
 

    std::cout << "Your binary in decimal: " << std::setprecision(100) << decimal_buffer << std::endl;



   

    




}

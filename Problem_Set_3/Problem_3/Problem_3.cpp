#include <iostream>
#include <fstream>
#include <vector>

void printV(std::vector<std::vector<double>>& v) {
    
    // Traversing the 2D vector
    for (auto& i : v) {
        for (auto& j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

struct FitConstants 
{
    double a_0 = 0;
    double a_1 = 0;
};

double Mean(std::vector<double> input)
{
    double sum = 0;

    for (int i = 0; i < input.size(); i++)
    {
        sum += input.at(i);
    }

    return sum / input.size();
}


FitConstants LinearRegression(std::vector<std::vector<double>> points)
{
    std::vector<double> fit_constants = {0,0};
    std::vector<double> x_values;
    std::vector<double> y_values;

    for (int i = 0; i < points.size(); i++)
        x_values.push_back(points[i][0]);
    
    for (int i = 0; i < points.size(); i++)
        y_values.push_back(points[i][1]);

    double s_xy = 0, s_xx = 0, sum = 0;

    for (int i = 0; i < points.size(); i++)
        sum += x_values.at(i) * y_values.at(i);

    s_xy = sum - (points.size() * Mean(x_values) * Mean(y_values));

    sum = 0;
    for (int i = 0; i < points.size(); i++)
        sum += (x_values.at(i) * x_values.at(i));

    s_xx = sum - points.size() * (Mean(x_values) * Mean(x_values));

    FitConstants fit;

    fit.a_1 = (s_xy / s_xx);
    fit.a_0 = Mean(y_values) - (fit.a_1 * Mean(x_values)); 

    return fit;
}

int main()
{
    std::ifstream input_file("data1.dat");

    std::vector<std::vector<double>> data;



    double temp1, temp2 = 0;

    //file opening checks
    if (input_file)
    {
        while (input_file >> temp1 >> temp2)
        {
            data.push_back({temp1, temp2});
        }
    }

    else
        std::cout << "Can't open data1.dat. File must be in same directory as this cpp file.";

    printV(data);

    FitConstants fit;

    fit = LinearRegression(data);

    std::cout << "a_0: " << fit.a_0 << std::endl << "a_1: " << fit.a_1 << std::endl;

}

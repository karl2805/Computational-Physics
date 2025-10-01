#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

void swap(std::vector<int>& array, int i, int j)
{
    int temp = array.at(i);
    array.at(i) = array.at(j);
    array.at(j) = temp;
}

void bubbleSort(std::vector<int>& array)
{
    int i, j;
    int n = array.size();
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (array.at(j) > array.at(j + 1))
                swap(array, j, j + 1);
}

int main()
{
    std::ifstream input_file("dice.dat");

    std::vector<int> dice_rolls;

    int temp1, temp2, counter = 0;


    //file opening checks
    if (input_file)
    {
        while (input_file >> temp1 >> temp2)
        {
            dice_rolls.push_back(temp2);
        }
    }

    else
        std::cout << "Can't open dice.dat. File must be in same directory as this cpp file.";

    double mean = 0;

    for (int i : dice_rolls)
    {
        mean += i;
    }

    mean /= dice_rolls.size();

    std::cout << "Mean: " << mean << "\n";

    double sd_numerator = 0;
    double sd_population, sd_sample = 0;

    for (int i : dice_rolls)
        sd_numerator += (i - mean) * (i - mean);

    sd_population = std::sqrt(sd_numerator / dice_rolls.size());
    sd_sample = std::sqrt(sd_numerator / (dice_rolls.size() - 1));

    std::cout << "Sd population: " << sd_population << "\n";
    std::cout << "Sd sample: " << sd_sample << "\n";

    bubbleSort(dice_rolls);

    double median = 0;

    //compute median depending on whether the number of data points is odd or even

    if (dice_rolls.size() % 2 != 0)
    {
        median = dice_rolls.at((dice_rolls.size()) / 2);
    }

    if (dice_rolls.size() % 2 == 0)
    {
        median = 0.5 * (dice_rolls.at((dice_rolls.size()) / 2 - 1) + dice_rolls.at((dice_rolls.size()) / 2));
    }

    std::cout << "Median: " << median << "\n";

    double difference = std::abs(mean - median);

    std::cout << "Difference between mean and median: " << difference << std::endl;
    std::cout << "Difference relative to the mean: " << ((difference) / mean) * 100 << '%' << '\n';
    std::cout << "Difference relative to the median: " << ((difference) / median) * 100 << '%' << '\n';

    
}
#include <iostream>
#include <cmath>

int main() 
{
    float delays_experienced[10] = {4, 10, 12, 55, 22, 15, 8, 7, 9, 8};

    std::cout << "Delays experienced: ";

    int counter = 0;
    float array_sum = 0;

    for (float i : delays_experienced)
    {
        std::cout << i;

        if (counter < 9)
            std:: cout << ", ";

        array_sum += i;
        counter++;
    }
    std::cout << " minutes";

    float mean = array_sum / 10;
    std::cout << "\nMean of data: " << mean << " minutes" << '\n';

    float sd_numerator = 0;
    float sd_population, sd_sample = 0;

    for (int i : delays_experienced)
        sd_numerator += (i - mean) * (i - mean);

    sd_population = sqrt(sd_numerator / 10);
    sd_sample = sqrt(sd_numerator / 9);

    
    std::cout << "Standard deviation of data as population: " << sd_population << " minutes" << '\n';
    std::cout << "Standard deviation of data as sample: " << sd_sample << " minutes" << '\n';

    float mean_no_outlier = (array_sum - 55) / 10;

    std::cout << "Mean of data excluding the 55 minute outlier: " << mean_no_outlier << " minutes" << '\n';
    std::cout << "Difference in mean with and without outlier: " << mean - mean_no_outlier << " minutes" << '\n';





    
    



    





}
#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <array>

//defining all the constants used in this programme
const double M_Sun = 1.989e30; // mass of sun in kg
const double M_Earth = 5.972e24; // mass of earth in kg
const double M_Jupiter = 1.898e27; // mass of Jupiter in kg
const double G = 6.674e-11; // gravatational constant 
const double AU = 1.496e11; // Astronomical Unit (meters)
const double Day = 60*60*24; //seconds in a day
const double Year = 365.25*Day;// seconds in a year
const double Hour = 60*60; //seconds in an hour
const double mu = G*(M_Earth + M_Sun);

typedef std::vector<std::vector<double>> Vec2;
typedef std::vector<double> Vec;
typedef std::array<double, 4> State; 
typedef std::array<double, 8> Two_State; 


double CrossProduct(const Vec& a, const Vec& b) // Returns only the z component of the cross product
{
	return (a[0] * b[1]) - (a[1] * b[0]);
}

//Defining operator overloading functions to handle addition and multiplication of state vectors
State operator*(double b, State a)
{
    return {a[0] * b, a[1] * b, a[2] * b, a[3] * b};
}

inline State operator*(State a, double b)
{
    return {a[0] * b, a[1] * b, a[2] * b, a[3] * b};
}

inline State operator+(State a, State b)
{
    return {a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]};
}

inline Two_State operator*(double b, Two_State a)
{
    return {a[0] * b, a[1] * b, a[2] * b, a[3] * b, a[4] * b, a[5] * b, a[6] * b, a[7] * b};
}

inline Two_State operator*(Two_State a, double b)
{
    return {a[0] * b, a[1] * b, a[2] * b, a[3] * b, a[4] * b, a[5] * b, a[6] * b, a[7] * b};
}

inline Two_State operator+(Two_State a, Two_State b)
{
    return {a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3], a[4] + b[4], a[5] + b[5], a[6] + b[6], a[7] + b[7]};
}

//Functions to write vectors to csv files for plotting
void SavetoCsv(std::string filename, Vec2& input, bool threecolumns)
{
	std::ofstream output(filename);

    if (!threecolumns)
    {
	    for (int i = 0; i < input.size(); i++)
	    	output << input[i][0] << "," << input[i][1] << std::endl;
    }

    else 
    {
        for (int i = 0; i < input.size(); i++)
		    output << input[i][0] << "," << input[i][1] << "," << input[i][2] <<std::endl;
    }
}

void SavetoCsv(std::string filename, Vec& trajectory)
{
	std::ofstream output(filename);

	for (int i = 0; i < trajectory.size(); i++)
		output << trajectory[i] << std::endl;
}


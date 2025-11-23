#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <array>

#include "constants.h"

typedef std::vector<std::vector<double>> Vec2;
typedef std::vector<double> Vec;
typedef std::array<double, 4> State; 
typedef std::array<double, 8> Two_State; 

double CrossProduct(const Vec& a, const Vec& b) // Data only the z component of the cross product
{
	return (a[0] * b[1]) - (a[1] * b[0]);
}

//Define multiply a state by a double
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

State EarthOrbit(State s) //Data the derivative of the elements of the state vector defined by the ODEs of the problem
{
    //calculate the magnitude of r to find acceleration later
    double r = std::sqrt(s[0] * s[0] + s[1] * s[1]);

    //calcualte the acceleration for the x and y components
    double a_x = (-G * M_Sun * s[0] ) / (r * r * r);
    double a_y = (-G * M_Sun * s[1] ) / (r * r * r);

    //return the derivative state using the velocities of the input state vector
    return {s[2], s[3], a_x, a_y};
}

State RK4Step(State (*f)(State s), State& s, double dt)
{
    State k1 = f(s);
    State k2 = f(s + 0.5 * k1 * dt);
    State k3 = f(s + 0.5 * k2 * dt);
    State k4 = f(s + k3 * dt);

    //perform rk4 step
    return s + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4) * dt;
}



State RK2StepRalston(State (*f)(State s), State& s, double dt)
{
    State k1 = f(s);
    State k2 = f(s + 0.25 * k1 * dt);

    //perform rk2 step
    return s + ((1.0/3.0) * k1 + (2.0/3.0) * k2) * dt;
}

State EulerStep(State (*f)(State s), State& s, double dt)
{
    return s + f(s) * dt;
}

struct Data //struct that saves all the data of the orbit
{
	Vec2 trajectory; //record the trajectory
	Vec2 L; //record the angular momentum
	Vec2 Energy; //record the energy
};

void RecordData(Data& data, const State& s, double time)
{
    //calculate the angular momentum and save
    Vec r_vec = {s[0], s[1]};
    Vec p_vec = {M_Earth * s[2], M_Earth * s[3]};

    data.L.push_back({time, CrossProduct(r_vec, p_vec)});

    //find magnitute of the current velocity
    double v = std::sqrt(s[2] * s[2] + s[3] * s[3]);

    //find the magnitude of the current r vector
    double r = std::sqrt(s[0] * s[0] + s[1] * s[1]);
    double energy = 0.5 * M_Earth * v * v - (G * M_Earth * M_Sun) / r;

    //save the energy with the current time for plotting
    data.Energy.push_back({time, energy});

    //save the current position trajectory
    data.trajectory.push_back({time, s[0], s[1]});
}



Data EulerMethod(State& intial_state, double running_time, double dt)
{
    Data data;
    State state = intial_state;

    //record the initial state
    RecordData(data, state, 0);

    for (double time = dt; time < running_time; time += dt)
    {
        //perform the euler step
        state = EulerStep(EarthOrbit, state, dt);

        //record the current state
        RecordData(data, state, time);
    }

    return data;
}

Data RK4Method(State& initial_state, double running_time, double dt)
{
    Data data;
    State state = initial_state;

    //record the initial state
    RecordData(data, state, 0);

    for (double time = dt; time < running_time; time += dt)
    {
        //perform the euler step
        state = RK4Step(EarthOrbit, state, dt);

        //record the current state
        RecordData(data, state, time);
    }

    return data;
}

Data RK2Method(State& initial_state, double running_time, double dt)
{
    Data data;
    State state = initial_state;

    //record the initial state
    RecordData(data, state, 0);

    for (double time = dt; time < running_time; time += dt)
    {
        //perform the euler step
        state = RK2StepRalston(EarthOrbit, state, dt);

        //record the current state
        RecordData(data, state, time);
    }

    return data;
}



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


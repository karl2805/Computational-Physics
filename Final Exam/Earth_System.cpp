#include "helper_functions.h"

struct Data //struct that saves all the data of the orbit
{
	Vec2 trajectory; //record the trajectory
	Vec2 L; //record the angular momentum
	Vec2 Energy; //record the energy
    Vec2 e; //record the eccentricity
};

void RecordData(Data& data, const State& s, double time) //function takes in a state vector and saves the parameters in a Data struct
{
    //calculate the angular momentum and save
    Vec r_vec = {s[0], s[1]};
    Vec p_vec = {M_Earth * s[2], M_Earth * s[3]};

    double L = CrossProduct(r_vec, p_vec);

    data.L.push_back({time, L});

    //find magnitute of the current velocity
    double v = std::sqrt(s[2] * s[2] + s[3] * s[3]);

    //find the magnitude of the current r vector
    double r = std::sqrt(s[0] * s[0] + s[1] * s[1]);
    //double energy = 0.5 * M_Earth * v * v - (G * M_Earth * M_Sun) / r;

    double energy = (-G * M_Sun * M_Earth) / r + 0.5 * M_Earth * v * v;

    //save the energy with the current time for plotting
    data.Energy.push_back({time, energy});

    //save the current position trajectory
    data.trajectory.push_back({time, s[0], s[1]});

    double h = L / M_Earth;

    double e = std::sqrt(1 + ((h*h) / (mu * mu)) * (v*v - (2*mu/r)));

    data.e.push_back({time, e});
}


State EarthOrbit(State s) //Calculates the derivative of the elements of the state vector defined by the ODEs of the problem
{
    //calculate the magnitude of r to find acceleration later
    double r = std::sqrt(s[0] * s[0] + s[1] * s[1]);

    //calcualte the acceleration for the x and y components
    double a_x = (-G * M_Sun * s[0] ) / (r * r * r);
    double a_y = (-G * M_Sun * s[1] ) / (r * r * r);

    //return the derivative state using the velocities of the input state vector
    return {s[2], s[3], a_x, a_y};
}

State EulerStep(State (*f)(State s), State& s, double dt)
{
    return s + f(s) * dt;
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

State RK2StepRalston(State (*f)(State s), State& s, double dt)
{
    State k1 = f(s);
    State k2 = f(s + 0.25 * k1 * dt);

    //perform rk2 step
    return s + ((1.0/3.0) * k1 + (2.0/3.0) * k2) * dt;
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

State RK4Step(State (*f)(State s), State& s, double dt)
{
    State k1 = f(s);
    State k2 = f(s + 0.5 * k1 * dt);
    State k3 = f(s + 0.5 * k2 * dt);
    State k4 = f(s + k3 * dt);

    //perform rk4 step
    return s + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4) * dt;
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

int main()
{
	//define the initial conditions
    double x_0  = AU;
    double y_0  = 0;
    double vx_0 = 0;
    double vy_0 = std::sqrt((G * M_Sun) / std::sqrt(x_0 * x_0 + y_0 * y_0)); //set initial y velocity to the Kepler velocity
    

    //put the initial conditions in a state vecotr
    State initial_state = {x_0, y_0, vx_0, vy_0};

    Data data; //define a data recording struct

    //Euler step = day
    data = EulerMethod(initial_state, Year*5, Day);
    SavetoCsv("CSVS/Day_Euler.csv", data.trajectory, true);
    SavetoCsv("CSVS/Day_L_Euler.csv", data.L, true);
    SavetoCsv("CSVS/Day_E_Euler.csv", data.Energy, true);

    //Euler step = half day
    data = EulerMethod(initial_state, Year*5, Day/2);
    SavetoCsv("CSVS/halfday_Euler.csv", data.trajectory, true);
    
    //Euler step = quarter day
    data = EulerMethod(initial_state, Year*5, Day/4);
    SavetoCsv("CSVS/quarterday_Euler.csv", data.trajectory, true);

    //RK2 step = day
    data = RK2Method(initial_state, Year*5, Day);
    SavetoCsv("CSVS/Day_RK2.csv", data.trajectory, true);
    SavetoCsv("CSVS/Day_L_RK2.csv", data.L, true);
    SavetoCsv("CSVS/Day_E_RK2.csv", data.Energy, true);
    
    //RK2 step = half day
    data = RK2Method(initial_state, Year*5, Day/2);
    SavetoCsv("CSVS/halfday_RK2.csv", data.trajectory, true);

    //RK2 step = quarter day
    data = RK2Method(initial_state, Year*5, Day/4);
    SavetoCsv("CSVS/quarterday_RK2.csv", data.trajectory, true);


    //RK4 step = day
    data = RK4Method(initial_state, Year*5, Day);
    SavetoCsv("CSVS/Day_RK4.csv", data.trajectory, true);
    SavetoCsv("CSVS/Day_L_RK4.csv", data.L, true);
    SavetoCsv("CSVS/Day_E_RK4.csv", data.Energy, true);
    
    //RK4 step = half day
    data = RK4Method(initial_state, Year*5, Day/2);
    SavetoCsv("CSVS/halfday_RK4.csv", data.trajectory, true);

    //RK4 step = quarter day
    data = RK4Method(initial_state, Year*5, Day/4);
    SavetoCsv("CSVS/quarterday_RK4.csv", data.trajectory, true);

}
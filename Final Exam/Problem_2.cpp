#include "functions.h"

State EarthWithJupiter(State e, State j) //Data the derivative of the elements of the state vector defined by the ODEs of the problem
{
    //calculate the magnitude of r to find acceleration later
    double r_s = std::sqrt(e[0] * e[0] + e[1] * e[1]);

    double r_j = std::sqrt((e[0] - j[0] * e[0] - j[0]) + (e[1] - j[1] * e[1] - j[1]));

    //calcualte the acceleration for the x and y components
    double a_x = (-G * M_Sun * e[0] ) / (r_s * r_s * r_s) + (-G * M_Jupiter * e[0] ) / (r_j * r_j * r_j);
    double a_y = (-G * M_Sun * e[1] ) / (r_s * r_s * r_s) + (-G * M_Jupiter * e[1] ) / (r_j * r_j * r_j);

    //return the derivative state using the velocities of the input state vector
    return {e[2], e[3], a_x, a_y};
}

State JupiterWithEarth(State j, State e) //Data the derivative of the elements of the state vector defined by the ODEs of the problem
{
    //calculate the magnitude of r to find acceleration later
    double r_s = std::sqrt(j[0] * j[0] + j[1] * j[1]);

    double r_e = std::sqrt((e[0] - j[0] * e[0] - j[0]) + (e[1] - j[1] * e[1] - j[1]));

    //calcualte the acceleration for the x and y components
    double a_x = (-G * M_Sun * e[0] ) / (r_s * r_s * r_s) + (-G * M_Jupiter * e[0] ) / (r_e * r_e * r_e);
    double a_y = (-G * M_Sun * e[1] ) / (r_s * r_s * r_s) + (-G * M_Jupiter * e[1] ) / (r_e * r_e * r_e);

    //return the derivative state using the velocities of the input state vector
    return {e[2], e[3], a_x, a_y};
}


int main()
{   
    //Set initial states of Earth and Jupiter
    double x_0, y_0, vx_0, vy_0;
    State earth_initial, jupiter_initial;

    //Earth
    x_0  = AU;
    y_0  = 0;
    vx_0 = 0;
    vy_0 = std::sqrt((G * M_Sun) / std::sqrt(x_0 * x_0 + y_0 * y_0)); //set initial y velocity to the Kepler velocity

    earth_initial = {x_0, y_0, vx_0, vy_0};

    //Jupiter
    x_0  = -5.2*AU; //set to opposite side of the sun
    y_0  = 0;
    vx_0 = 0;
    vy_0 = -std::sqrt((G * M_Sun) / std::sqrt(x_0 * x_0 + y_0 * y_0)); //set initial y velocity to the Kepler velocity

    jupiter_initial = {x_0, y_0, vx_0, vy_0};

    Data earth_data;
    Data jupiter_data;

    double time = 0;

    RecordData(earth_data, earth_initial, time);
    RecordData(jupiter_data, jupiter_initial, time);

    State jupiter = jupiter_initial;
    State earth = earth_initial;

    double running_time = 10*Year;
    double dt = Day*2;

    for (time = dt; time < running_time; time += dt)
    {
        //perform the euler step
        earth = RK4Step(EarthWithJupiter, earth, jupiter, dt);

        //record the current state
        RecordData(earth_data, earth, time);
    }

    SavetoCsv("CSVS/JupiterTest.csv", earth_data.trajectory, true);
    


}
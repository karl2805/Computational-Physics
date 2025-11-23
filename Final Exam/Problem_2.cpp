#include "functions.h"
#include <algorithm>

Two_State JupiterEarthSystem(Two_State s)
{
    //calculate the magnitue of radius of orbit to sun for earth and jupiter
    double r_e = std::sqrt(s[0] * s[0] + s[1] * s[1]);
    double r_j = std::sqrt(s[4] * s[4] + s[5] * s[5]);

    //calculate the distance d between earth and jupiter
    double d = std::sqrt((s[0] - s[4])*(s[0] - s[4]) + (s[1] - s[5])*(s[1] - s[5]));
    double d_x = s[4] - s[0];
    double d_y = s[5] - s[1]; 

    //new acceleration components for earth
    double a_x_earth = (-G * M_Sun * s[0] ) / (r_e * r_e * r_e) + (G * M_Jupiter * d_x ) / (d * d * d);
    double a_y_earth = (-G * M_Sun * s[1] ) / (r_e * r_e * r_e) + (G * M_Jupiter * d_y ) / (d * d * d);
    
    //new acceleration components for jupiter
    double a_x_jupiter = (-G * M_Sun * s[4] ) / (r_j * r_j * r_j) + (-G * M_Earth * d_x ) / (d * d * d);
    double a_y_jupiter = (-G * M_Sun * s[5] ) / (r_j * r_j * r_j) + (-G * M_Earth * d_y ) / (d * d * d);

    return{s[2], s[3], a_x_earth, a_y_earth, s[6], s[7], a_x_jupiter, a_y_jupiter};
}

Two_State RK4Step(Two_State (*f)(Two_State s), Two_State& s, double dt)
{
    Two_State k1 = f(s);
    Two_State k2 = f(s + 0.5 * k1 * dt);
    Two_State k3 = f(s + 0.5 * k2 * dt);
    Two_State k4 = f(s + k3 * dt);

    //perform rk4 step
    return s + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4) * dt;
}

int main()
{   
    //Set initial states of Earth and Jupiter
    double xe_0, ye_0, vxe_0, vye_0, xj_0, yj_0, vxj_0, vyj_0;
    Two_State earth_jupiter;

    //Earth
    xe_0  = AU;
    ye_0  = 0;
    vxe_0 = 0;
    vye_0 = std::sqrt((G * M_Sun) / std::sqrt(xe_0 * xe_0 + ye_0 * ye_0)); //set initial y velocity to the Kepler velocity

    //Jupiter
    xj_0  = -5.2*AU; //set to opposite side of the sun
    yj_0  = 0;
    vxj_0 = 0;
    vyj_0 = -std::sqrt((G * M_Sun) / std::sqrt(xj_0 * xj_0 + yj_0 * yj_0)); //set initial y velocity to the Kepler velocity
    

    earth_jupiter = {xe_0, ye_0, vxe_0, vye_0, xj_0, yj_0, vxj_0, vyj_0};

    Data earth_data;
    Data jupiter_data;

    double time = 0;

    State earth = {xe_0, ye_0, vxe_0, vye_0};
    State jupiter = {xj_0, yj_0, vxj_0, vyj_0};

    RecordData(earth_data, earth, time);
    RecordData(jupiter_data, jupiter, time);

    double running_time = 12*Year;
    double dt = Day;

    for (time = dt; time < running_time; time += dt)
    {
        //perform the RK4 step
        earth_jupiter = RK4Step(JupiterEarthSystem, earth_jupiter, dt);

        //record the current state
        std::copy(earth_jupiter.begin(), earth_jupiter.begin() + 4, earth.begin());
        std::copy(earth_jupiter.begin() + 4, earth_jupiter.end(), jupiter.begin());

        RecordData(earth_data, earth, time);
        RecordData(jupiter_data, jupiter, time);
    }

    SavetoCsv("CSVS/Earth_With_Jupiter.csv", earth_data.trajectory, true);
    SavetoCsv("CSVS/Earth_With_Jupiter_Earth_L.csv", earth_data.L, false);
    SavetoCsv("CSVS/Earth_With_Jupiter_Earth_E.csv", earth_data.Energy, false);
    
    SavetoCsv("CSVS/Jupiter_With_Earth.csv", jupiter_data.trajectory, true);
    SavetoCsv("CSVS/Earth_With_Jupiter_Jupiter_L.csv", jupiter_data.L, false);
    SavetoCsv("CSVS/Earth_With_Jupiter_Jupiter_E.csv", jupiter_data.Energy, false);
    


}
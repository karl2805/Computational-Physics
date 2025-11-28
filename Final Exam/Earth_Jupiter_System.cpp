#include "helper_functions.h"
#include <algorithm>

struct Data2 //struct that saves all the data of the orbit
{
	Vec2 earth_trajectory; //record the trajectory
	Vec2 earth_L; //record the angular momentum
	Vec2 earth_Energy; //record the energy
    
    Vec2 jupiter_trajectory;
    Vec2 jupiter_L;
    Vec2 jupiter_Energy;

    Vec2 total_Energy;
};

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
    double a_x_earth = (-G * M_Sun * s[0] ) / (r_e * r_e * r_e) + (-G * M_Jupiter * d_x ) / (d * d * d);
    double a_y_earth = (-G * M_Sun * s[1] ) / (r_e * r_e * r_e) + (-G * M_Jupiter * d_y ) / (d * d * d);
    
    //new acceleration components for jupiter
    double a_x_jupiter = (-G * M_Sun * s[4] ) / (r_j * r_j * r_j) + (G * M_Earth * d_x ) / (d * d * d);
    double a_y_jupiter = (-G * M_Sun * s[5] ) / (r_j * r_j * r_j) + (G * M_Earth * d_y ) / (d * d * d);

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

void RecordData(Data2& data, const Two_State s, double time) //This function takes in a two_state vector and saves the current properties of the system
{
    double xe = s[0];
    double ye = s[1];
    double vxe = s[2];
    double vye = s[3];
    double xj = s[4];
    double yj = s[5];
    double vxj = s[6];
    double vyj = s[7];

    //calculate position of centre of mass to find the angular momentum
    double xcom = (M_Earth * xe + M_Jupiter * xj) / (M_Earth + M_Jupiter + M_Sun);
    double ycom = (M_Earth * ye + M_Jupiter * yj) / (M_Earth + M_Jupiter + M_Sun);

    //find the position vector from the centre of mass
    Vec r_vec = {(xe - xcom), (ye - ycom)};

    //find the momentum vector
    Vec p_vec = {M_Earth * vxe, M_Earth * vye};

    //calculate the angular momentum
    double L = CrossProduct(r_vec, p_vec);

    //the initial angular momentum. Static makes it only be set once
    static double L_earth_initial = L;

    //save the angular momentum relative to the initial angular momentum
    data.earth_L.push_back({time, L - L_earth_initial});
    
    //calculate the angular momentum of Jupiter and save
    r_vec = {xj - xcom, yj - ycom};
    p_vec = {M_Jupiter * vxj, M_Jupiter * vyj};

    L = CrossProduct(r_vec, p_vec);

    static double L_jupiter_initial = L;

    data.jupiter_L.push_back({time, L - L_jupiter_initial});

    //find magnitute of the current velocity for earth and jupiter
    double v_earth = std::sqrt(vxe * vxe + vye * vye);
    double v_jupiter = std::sqrt(vxj * vxj + vyj * vyj);

    //find the magnitude of the current r vector for earth and jupiter
    double r_earth = std::sqrt(xe * xe + ye * ye);
    double r_jupiter = std::sqrt(xj * xj + yj * yj);

    //find the distance d between earth and jupiter
    double d = std::sqrt((xe - xj)*(xe - xj) + (ye - yj)*(ye - yj));
    
    //calcualte the energy of earth and jupiter adding the potential between the Earth and Jupiter
    double potential_between = (-G * M_Earth * M_Jupiter) / d;
    double energy_earth = ((-G * M_Sun * M_Earth) / r_earth) + 0.5 * M_Earth * v_earth * v_earth + 0.5 * potential_between;
    double energy_jupiter = ((-G * M_Sun * M_Jupiter) / r_jupiter) + 0.5 * M_Jupiter * v_jupiter * v_jupiter + 0.5 * potential_between;


    //setting variables to the initila energy and earth and jupiter
    static double energy_jupiter_initial = energy_jupiter;
    static double energy_earth_initial = energy_earth;

    double total_energy = energy_earth + energy_jupiter;
    static double total_energy_initial = total_energy;

    //save the energy of earth and jupiter relative to the initial condition with the current time for plotting
    data.earth_Energy.push_back({time, energy_earth - energy_earth_initial});
    data.jupiter_Energy.push_back({time, energy_jupiter - energy_jupiter_initial});

    //save the current position trajectory
    data.earth_trajectory.push_back({time, xe, ye});
    data.jupiter_trajectory.push_back({time, xj, yj});

    data.total_Energy.push_back({time, total_energy - total_energy_initial});
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
    

    //Jupiter
    xj_0  = -5.2*AU; //set to opposite side of the sun
    yj_0  = 0;
    vxj_0 = 0;
    

    double r_e = std::sqrt(xe_0*xe_0 + ye_0*ye_0);
    double r_j = std::sqrt(xj_0*xj_0 + yj_0*yj_0);
    
    vyj_0 = -std::sqrt((G * M_Sun) / r_j);
    vye_0 = std::sqrt((G * M_Sun) / r_e);

    //put the initial conditions in a state vector
    earth_jupiter = {xe_0, ye_0, vxe_0, vye_0, xj_0, yj_0, vxj_0, vyj_0};

    Data2 system;


    double time = 0;

    //record the inital conditions of the orbit
    RecordData(system, earth_jupiter, time);
   

    double running_time = Year*24;
    double dt = Day;

    //The integration loop
    for (time = dt; time < running_time; time += dt)
    {
        //perform the RK4 step
        earth_jupiter = RK4Step(JupiterEarthSystem, earth_jupiter, dt);

        RecordData(system, earth_jupiter, time);
    }

    //Save the recorded data to CSV files for plotting
    SavetoCsv("CSVS/Earth_With_Jupiter.csv", system.earth_trajectory, true);
    SavetoCsv("CSVS/Earth_With_Jupiter_Earth_L.csv", system.earth_L, false);
    SavetoCsv("CSVS/Earth_With_Jupiter_Earth_E.csv", system.earth_Energy, true);
    
    SavetoCsv("CSVS/Jupiter_With_Earth.csv", system.jupiter_trajectory, true);
    SavetoCsv("CSVS/Earth_With_Jupiter_Jupiter_L.csv", system.jupiter_L, false);
    SavetoCsv("CSVS/Earth_With_Jupiter_Jupiter_E.csv", system.jupiter_Energy, false);

    SavetoCsv("CSVS/totalenergy.csv", system.total_Energy, false);
    
    

}
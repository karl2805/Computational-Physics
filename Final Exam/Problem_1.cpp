#include "functions.h"

int main()
{
	//define the initial conditions
    double x_0  = AU;
    double y_0  = 0;
    double vx_0 = 0;
    double vy_0 = std::sqrt((G * M_Sun) / std::sqrt(x_0 * x_0 + y_0 * y_0)); //set initial y velocity to the Kepler velocity
    

    //put the initial conditions in a state vecotr
    State initial_state = {x_0, y_0, vx_0, vy_0};

    Data data;

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
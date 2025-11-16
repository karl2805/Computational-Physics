#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

typedef std::vector<std::vector<double>> Vec2;
typedef std::vector<double> Vec;


const double M_Sun = 1.989e30; // mass of sun in kg
const double M_Earth = 5.972e24; // mass of earth in kg
const double G = 6.674e-11; // gravatational constant 
const double AU = 1.496e11; // Astronomical Unit (meters)
const double Day = 60*60*24; //seconds in a day
const double Year = 365.25*Day;// seconds in a year
const double Hour = 60*60;

double CrossProduct(const Vec& a, const Vec& b) // returns only the z compnent of the cross product
{
	return (a[0] * b[1]) - (a[1] * b[0]);
}

struct Returns
{
	Vec2 trajectory; //record the trajectory
	Vec2 L; //record the angular momentum
	Vec2 Energy;
};

Returns OrbitEulerMethod(double dt, double running_time=Year)
{
	
	Vec2 trajectory;
	Vec2 L; //array to save the angular momentums
	Vec2 Energy;

	int num_steps = running_time / dt + 1;

	//define the initial conditions
	double x = AU;
	double y = 0;
	double r = std::sqrt(x*x + y*y);

	std::vector<double> current_pos = { x, y };

	//put initial values into the trajectory array
	trajectory.push_back(current_pos);

	//define initial velocities
	double v_x = 0;
	double v_y = std::sqrt((G * M_Sun) / x);

	//define initial accelleration
	double a_x = (-G * M_Sun * x) / (r * r * r);
	double a_y = (-G * M_Sun * y) / (r * r * r); 
	
	//calculate the initial angular momentum L
	Vec p_vec = {M_Earth * v_x, M_Earth * v_y, 0};
	Vec r_vec = {x, y, 0};

	double l = CrossProduct(r_vec, p_vec);

	L.push_back({0, l});

	for (int i = 1; i <= num_steps; i++)
	{
		//calcaulte the magnitude of r
		r = std::sqrt(x * x + y * y);

		//euler step the positions
		x += v_x * dt;
		y += v_y * dt;

		//euler step the velocities
		v_x += a_x * dt;
		v_y += a_y * dt;
		
		//calaulate the dv_x/dt = a_x and dv_y/dt = a_y
		a_x = (-G * M_Sun * x) / (r * r * r);
		a_y = (-G * M_Sun * y) / (r * r * r);



		//save the current positions
		current_pos = { x, y };
		trajectory.push_back(current_pos);

		//calculate angular momentum and save to the array
		Vec r_vec = {x, y, 0};
		Vec p_vec = {M_Earth * v_x, M_Earth * v_y, 0};

		l = CrossProduct(r_vec, p_vec);

		L.push_back({dt * i, l});

		//calculate the total energy
		double velocity = std::sqrt(v_x*v_x + v_y*v_y);
		double energy = 0.5 * M_Earth * velocity * velocity - (G * M_Earth * M_Sun)  / r;

		Energy.push_back({dt * i, energy});
	}

	return {trajectory, L, Energy};

}

Returns RungeKutta4thOrderOrbital(double dt, double running_time = Year)
{
    Vec2 trajectory;
    Vec2 L;
    Vec2 Energy;

    int num_steps = running_time / dt + 1;

    // Initial conditions
    double x = AU;
    double y = 0;

    double v_x = 0;
    double v_y = std::sqrt((G * M_Sun) / x);

    double r = std::sqrt(x * x + y * y);

    std::vector<double> current_pos = { x, y };
    trajectory.push_back(current_pos);

    // Initial angular momentum
    Vec p_vec = { M_Earth * v_x, M_Earth * v_y, 0 };
    Vec r_vec = { x, y, 0 };
    double l = CrossProduct(r_vec, p_vec);
    L.push_back({ 0, l });

    for (int i = 1; i <= num_steps; i++)
    {
        // -------- RK4 FOR POSITION (x,y) --------

        // k1
        double k1_x = v_x;
        double k1_y = v_y;

        // compute a_x, a_y using current x,y
        r = std::sqrt(x * x + y * y);
        double a_x = (-G * M_Sun * x) / (r * r * r);
        double a_y = (-G * M_Sun * y) / (r * r * r);

        double k1_vx = a_x;
        double k1_vy = a_y;

        // k2
        double x2 = x + 0.5 * dt * k1_x;
        double y2 = y + 0.5 * dt * k1_y;
        double vx2 = v_x + 0.5 * dt * k1_vx;
        double vy2 = v_y + 0.5 * dt * k1_vy;

        double r2 = std::sqrt(x2 * x2 + y2 * y2);
        double a2_x = (-G * M_Sun * x2) / (r2 * r2 * r2);
        double a2_y = (-G * M_Sun * y2) / (r2 * r2 * r2);

        double k2_x = vx2;
        double k2_y = vy2;
        double k2_vx = a2_x;
        double k2_vy = a2_y;

        // k3
        double x3 = x + 0.5 * dt * k2_x;
        double y3 = y + 0.5 * dt * k2_y;
        double vx3 = v_x + 0.5 * dt * k2_vx;
        double vy3 = v_y + 0.5 * dt * k2_vy;

        double r3 = std::sqrt(x3 * x3 + y3 * y3);
        double a3_x = (-G * M_Sun * x3) / (r3 * r3 * r3);
        double a3_y = (-G * M_Sun * y3) / (r3 * r3 * r3);

        double k3_x = vx3;
        double k3_y = vy3;
        double k3_vx = a3_x;
        double k3_vy = a3_y;

        // k4
        double x4 = x + dt * k3_x;
        double y4 = y + dt * k3_y;
        double vx4 = v_x + dt * k3_vx;
        double vy4 = v_y + dt * k3_vy;

        double r4 = std::sqrt(x4 * x4 + y4 * y4);
        double a4_x = (-G * M_Sun * x4) / (r4 * r4 * r4);
        double a4_y = (-G * M_Sun * y4) / (r4 * r4 * r4);

        double k4_x = vx4;
        double k4_y = vy4;
        double k4_vx = a4_x;
        double k4_vy = a4_y;

        // Update x, y, vx, vy using RK4
        x  += dt * (k1_x  + 2*k2_x  + 2*k3_x  + k4_x ) / 6.0;
        y  += dt * (k1_y  + 2*k2_y  + 2*k3_y  + k4_y ) / 6.0;
        v_x += dt * (k1_vx + 2*k2_vx + 2*k3_vx + k4_vx) / 6.0;
        v_y += dt * (k1_vy + 2*k2_vy + 2*k3_vy + k4_vy) / 6.0;

        // Save position
        current_pos = { x, y };
        trajectory.push_back(current_pos);

        // Angular momentum
        Vec r_vec = { x, y, 0 };
        Vec p_vec = { M_Earth * v_x, M_Earth * v_y, 0 };
        l = CrossProduct(r_vec, p_vec);
        L.push_back({ dt * i, l });

        // Energy
        double velocity = std::sqrt(v_x * v_x + v_y * v_y);
        double energy = 0.5 * M_Earth * velocity * velocity -
                        (G * M_Earth * M_Sun) / std::sqrt(x * x + y * y);
        Energy.push_back({ dt * i, energy });
    }

    return { trajectory, L, Energy };
}



void SavetoCsv(std::string filename, Vec2& trajectory)
{
	std::ofstream output(filename);

	for (int i = 0; i < trajectory.size(); i++)
		output << trajectory[i][0] << "," << trajectory[i][1] << std::endl;
}

void SavetoCsv(std::string filename, Vec& trajectory)
{
	std::ofstream output(filename);

	for (int i = 0; i < trajectory.size(); i++)
		output << trajectory[i] << std::endl;
}



int main()
{
	
	auto returns = OrbitEulerMethod(Day, 10*Year); //solve with timestep of a day
	SavetoCsv("Day.csv", returns.trajectory);
	SavetoCsv("Momentum.csv", returns.L);
	SavetoCsv("Energy.csv", returns.Energy);
	
	returns = OrbitEulerMethod(Day*5, 10*Year); //solve with time step of 5 days
	SavetoCsv("halfday.csv", returns.trajectory);

	returns = OrbitEulerMethod(Day*10, 10*Year); //solve with time step of 10 days
	SavetoCsv("quarterday.csv", returns.trajectory);





	returns = RungeKutta4thOrderOrbital(Day, 10*Year); //solve with timestep of a day
	SavetoCsv("Day_Rutta.csv", returns.trajectory);
	SavetoCsv("Momentum_Rutta.csv", returns.L);
	SavetoCsv("Energy_Rutta.csv", returns.Energy);
	
	returns = OrbitEulerMethod(Day*0.5, 10*Year); //solve with time step of 5 days
	SavetoCsv("halfday_Rutta.csv", returns.trajectory);

	returns = OrbitEulerMethod(Day*0.1, 10*Year); //solve with time step of 10 days
	SavetoCsv("quarterday_Rutta.csv", returns.trajectory);




}
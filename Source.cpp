#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
using namespace std;

double f1(double x)
{
	
	return cos(x) * tanh(x);
}

double f2(double x)
{
	return cos(x) * tanh(x) * sin(5 * x);
}

double random(double min, double max)
{
	double d = max - min;
	double r = (double)rand() / RAND_MAX * d;
	return min + r;
	
}


void anneling_simulation2(double a, double b, double Tmax, double Tmin, double ALPHA, double (*f)(double)) {

	srand(0);

	double Ti = Tmax;

	double x0 = random(a, b);
	double fx0 = f(x0);

	cout << "______________________________________________________________________" << endl;
	cout << "  N |           T     |         x    |        f(x)   |          P    | " << endl;
	cout << "______________________________________________________________________" << endl;

	int N = 0;

	while (Ti > Tmin) {
		double x1 = random(a, b);
		double fx1 = f(x1);
		double PDelta = 0;
		double delta = fx1 - fx0;
		if (delta <= 0) {

			x0 = x1;
		}
		else {
			PDelta = exp(-delta / Ti);
			double p = random(0, 1);
			if (p <= PDelta) {
				x0 = x1;
			}

		}
		fx0 = f(x0);
		std::cout.precision(7);
		
		std::cout << ++N << setprecision(7)<<"             " << Ti  << setprecision(7) << "       " <<x0 <<  setprecision(7) << "         " << fx0 <<  setprecision(7) << "          " <<PDelta << std::endl;
		
		Ti *= ALPHA;
	}

	cout << f(x0) << endl;



}


int main()
{
	double a = 1.5;
	double b = 4.0;
	double Tmax = 10000;
	double Tmin = 0.01;
	double ALPHA = 0.95;
	double delta = 0.1;

	anneling_simulation2(a, b, Tmax, Tmin, ALPHA, f1);
	anneling_simulation2(a, b, Tmax, Tmin, ALPHA, f2);


	
	system("pause");
}

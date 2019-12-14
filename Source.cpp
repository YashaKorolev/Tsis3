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


void anneling_simulation(double a, double b, double Tmax, double Tmin, double ALPHA, double (*f)(double)) {

	srand(0);

	double Ti = Tmax;

	double x0 = random(a, b);
	double fx0 = f(x0);

	cout << "____________________________________________________________" << endl;
	cout << "  N |      T     |    x    |   f(x)   |       P      | Chg |" << endl;
	cout << "____________________________________________________________" << endl;

	int N = 0;

	while (Ti > Tmin) {
		double x1 = random(a, b);
		double fx1 = f(x1);
		double PDelta = 1;
		double delta = fx1 - fx0;
		bool flag = false;

		if (delta <= 0) {
			flag = true;
			x0 = x1;
		}
		else {
			PDelta = exp(-delta / Ti);
			double p = random(0, 1);
			if (p <= PDelta) {
				flag = true;
				x0 = x1;
			}

		}
		fx0 = f(x0);

		printf("%3i | %10.4lf | %02.5lf | % 5.5lf | %1.10lf | %3c |\n", ++N, Ti, x0, fx0, PDelta, flag ? '+' : '-');
		flag = false;

		Ti *= ALPHA;
	}
	cout << "\n\n";
	cout << "Minimum = f(" << x0 << ") = " << f(x0) << endl;
}

int main()
{
	double a = 1.5;
	double b = 4.0;
	double Tmax = 10000;
	double Tmin = 0.01;
	double ALPHA = 0.95;
	double delta = 0.1;
	cout << "\n\nUnimodal_function_annealing_method:\n\n";
	cout << "f(x)= cos(x) * tanh(x)" << endl << endl;
	anneling_simulation(a, b, Tmax, Tmin, ALPHA, f1);
	cout << "\n\n\n";
	cout << "\n\nMultimodal_function_annealing_method:\n\n";
	cout << "f(x)= cos(x) * tanh(x) * sin(5x)" << endl << endl;
	anneling_simulation(a, b, Tmax, Tmin, ALPHA, f2);

	system("pause");
}

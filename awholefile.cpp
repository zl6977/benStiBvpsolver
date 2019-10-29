#include <iostream>
#include <boost/array.hpp>
#include <vector>
#include <boost/numeric/odeint.hpp>
#include <math.h>
#include "bvpsolvezzz.h"
#define pi 3.1415926

using namespace std;
using namespace boost::numeric::odeint;

/* class bvpsolvezzz 
{
private:
	vector<double> resulty, resultdydx;
	static boost::array<double, 3> resulty_end;
	static double EI(double x);
	static double dEI(double x);

public:
	static double max_k,
		D1,
		d1,
		d2,
		L1,
		L2,
		L3,
		EIp,
		Es,
		F,
		q;

	bvpsolvezzz();
	void bvpsolvezzz_ini(
		double _max_k, double _D1, double _d1, double _d2,
		double _L1, double _L2, double _L3,
		double _EIp, double _Es, double _F, double _q);
	~bvpsolvezzz();
	static void write_targetFunc_end(const state_type &y, const double x);
	static void targetFunc(const state_type &y, state_type &dydx, double x);
	static void write_targetFunc(const state_type &y, const double x);
	size_t bvpsolver_zzz(func_pr system,
						 double ya, double yb,
						 double xa, double xb,
						 double dx, observer_pr observer0, observer_pr observer);
}; */
vector<double> resulty, resultdydx;
boost::array<double, 3> resulty_end;
double max_k,
	D1,
	d1,
	d2,
	L1,
	L2,
	L3,
	EIp,
	Es,
	F,
	q;

void bvpsolvezzz_ini(
	double _max_k, double _D1, double _d1, double _d2,
	double _L1, double _L2, double _L3,
	double _EIp, double _Es, double _F, double _q)
{
	max_k = _max_k;
	D1 = _D1;
	d1 = _d1;
	d2 = _d2;
	L1 = _L1;
	L2 = _L2;
	L3 = _L3;
	EIp = _EIp;
	Es = _Es;
	F = _F;
	q = _q;
}

void targetFunc(const state_type &y, state_type &dydx, double x)
{
	/*
    dxdt[2] = -b * x[2] + x[0] * x[1];*/
	dydx[0] = y[1];
	dydx[1] = -(dEI(x) * y[1] + F * sin(q - y[0])) / EI(x);
	// dydx[1] = -2.0 * y[1] / x - y[0] / x / x / x / x;
	// -(dEI*y(2)+F*sin(q-y(1)))/EI
}

void write_targetFunc(const state_type &y, const double x)
{
	//    cout << t << '\t' << x[0] << '\t' << x[1] << '\t' << x[2] << endl;
	cout << x << '\t' << y[0] << '\t' << y[1] << endl;
	/* 	resultx.push_back(t);
	for (int i = 0; i <= 1; i++)
		resultx.push_back(x[i]);  */
}

void write_targetFunc_end(const state_type &y, const double x)
{
	resulty_end[0] = x;
	resulty_end[1] = y[0];
	resulty_end[2] = y[1];
}

size_t bvpsolver_zzz(func_pr system,
					 double ya, double yb,
					 double xa, double xb,
					 double dx, observer_pr observer0, observer_pr observer)
{
	size_t count = 0;
	//	typename odeint::unwrap_reference< Observer >::type &obs = observer;
	double s_guess = (yb - ya) / (xb - xa), s_guess_pre = 0;
	double fais = yb, fais_pre = 0, dfaids = 0;
	state_type y; // initial conditions

	do
	{
		y = {{ya, s_guess}};
		// observer_pr ob_pr = this->write_targetFunc_end;
		integrate(system, y, xa, xb, dx, observer0);
		fais_pre = fais;
		fais = resulty_end[1] - yb;
		dfaids = (fais - fais_pre) / (s_guess - s_guess_pre);
		s_guess_pre = s_guess;
		s_guess = s_guess - fais / dfaids;
		count++;
	} while (fais > 0.001 * yb + 1e-6 || fais < -0.001 * yb - 1e-6);
	y = {{ya, s_guess}};
	integrate(system, y, xa, xb, dx, observer);
	return count;
}

double EI(double x)
{
	double Ds, EI, Is;
	if (x < L1)
	{
		Ds = D1;
		Is = pi / 64 * (pow(Ds, 4) - pow(d1, 4));
		EI = Es * Is + EIp;
	}
	else if (x < L1 + L2)
	{
		Ds = D1 - ((D1 - d2) / L2) * (x - L1);
		Is = pi / 64 * (pow(Ds, 4) - pow(d1, 4));
		EI = Es * Is + EIp;
	}
	else if (x < L1 + L2 + L3)
	{
		Ds = d2;
		Is = pi / 64 * (pow(Ds, 4) - pow(d1, 4));
		EI = Es * Is + EIp;
	}
	else
	{
		Ds = d1;
		Is = pi / 64 * (pow(Ds, 4) - pow(d1, 4));
		EI = Es * Is + EIp;
	}
	return EI;
}
double dEI(double x)
{
	double Ds, dEI;
	if (x < L1)
		dEI = 0;
	else if (x < L1 + L2)
	{
		Ds = D1 - ((D1 - d2) / L2) * (x - L1);
		dEI = -Es * pi / 64 * pow(Ds, 3) * 4 * (D1 - d2) / L2;
	}
	else if (x < L1 + L2 + L3)
		dEI = 0;
	else
		dEI = 0;
	return dEI;
}
/* extern "C" __declspec(dllexport) *createBvpSolver()
{
	return new bvpsolvezzz;
} */
int main(int argc, char **argv)
{
	// bvpsolvezzz *bvp = createBvpSolver();
	// bvpsolvezzz_ini(0.3, 0.7, 0.18, 0.2, 0.1, 2.3, 0.2, 1e4, 4.5e6, 2e4, 0.52);
	if (argc < 11)
	{
		cout << "insufficient parameters" << endl;
		return 0;
	}
	else
	{
		bvpsolvezzz_ini(atof(argv[1]),
						atof(argv[2]),
						atof(argv[3]),
						atof(argv[4]),
						atof(argv[5]),
						atof(argv[6]),
						atof(argv[7]),
						atof(argv[8]),
						atof(argv[9]),
						atof(argv[10]),
						atof(argv[11]));
		bvpsolver_zzz(targetFunc, 0.0, q, 0.0, 5.0, 0.0001, write_targetFunc_end, write_targetFunc);
		// bvpsolver_zzz(targetFunc, 0.0, 5 * sin(1), 1.0 / 3.0 / 3.14, 1.0, 0.001, write_targetFunc_end, write_targetFunc);
		// bvpsolver_zzz(targetFunc, 0.0, 5*sin(1), 1.0 / 3.0 / 3.14, 1.0, 0.001, write_targetFunc);
	}
}
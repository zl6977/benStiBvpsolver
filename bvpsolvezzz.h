// #pragma once
#ifndef _BVPSOLVEZZ_
#define _BVPSOLVEZZ_
#include <iostream>
#include <boost/array.hpp>
#include <vector>
#include <boost/numeric/odeint.hpp>
#include <math.h>

using namespace std;
using namespace boost::numeric::odeint;

typedef boost::array<double, 2> state_type;
/* typedef void (*func_pr)(const state_type, state_type, double);
typedef void (*observer_pr)(const state_type, double); */


void bvpsolvezzz_ini(
	double _max_k, double _D1, double _d1, double _d2,
	double _L1, double _L2, double _L3,
	double _EIp, double _Es, double _F, double _q);
double EI(double x);
double dEI(double x);
void write_targetFunc_end(const state_type &y, const double x);
void targetFunc(const state_type &y, state_type &dydx, double x);
void write_targetFunc(const state_type &y, const double x);
typedef decltype(targetFunc) func_pr;
typedef decltype(write_targetFunc) observer_pr;
size_t bvpsolver_zzz(func_pr system,
					 double ya, double yb,
					 double xa, double xb,
					 double dx, observer_pr observer0, observer_pr observer);
// extern "C" __declspec(dllexport) bvpsolvezzz *createBvpSolver();
#endif
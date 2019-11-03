# benStiBvpsolver
using a BVPSolver written by myself with boost library

call awholefile.exe in CMD by "awholefile.exe 0.3 0.7 0.18 0.2 0.1 2.3 0.2 1e4 4.5e6 2e4 0.52"
the parameters list is : double _max_k, double _D1, double _d1, double _d2,
	                      double _L1, double _L2, double _L3,
		                    double _EIp, double _Es, double _F, double _q

At first, in order to package the parameters and bvpsolver, I tried to to package the bvpsolver in dll using a class.
but now it must be abandoned for the reasons below:
1. the ivp solver in boost library only receives the pointer-to-function;
2. the bvpsolver in a class is pointer-to-member-function, which cannot conver to pointer-to-function;

so, I have to package the bvpsolver in an exe file, which can be called conveniently in other program.

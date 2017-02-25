/* Declaration of class CurveFitting */

#ifndef CURVEFITTING_H
#define CURVEFITTING_H

#include <Eigen/Dense>

using namespace Eigen;

class CurveFitting {
public:
	void readFile(int, int);
	void polynomial(int);
	void curvefitting(int);
	double getMean();
	double getVar();
	double getDist();
	double getPrice(int);
	void print(int);

private:
	const int M = 9;				//degree of the polynomial
	const double ALPHA = 0.005;		//precision of prior weights distribution
	const double BETA = 11.1;		//precision of target
	double td[256] = { 0 };			//training data
	double poly[256][10] = { 0 };
	double mean = 0;
	double var = 0;
	double pre_dist = 0;
};

#endif

/* member functions of class CurveFitting */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <Eigen/Dense>
#include "CurveFitting.h"

using namespace std;
using namespace Eigen;

void CurveFitting::readFile(int choice, int n)
{
	string filename;
	switch (choice) {
	case 1:
		//ifstream fin("aapl.csv");
		filename = "aapl.csv";
		break;
	case 2:
		filename = "baba.csv";
		break;
	case 3:
		filename = "bac.csv";
		break;
	case 4:
		filename = "f.csv";
		break;
	case 5:
		filename = "fb.csv";
		break;
	case 6:
		filename = "gld.csv";
		break;
	case 7:
		filename = "goog.csv";
		break;
	case 8:
		filename = "lng.csv";
		break;
	case 9:
		filename = "msft.csv";
		break;
	case 10:
		filename = "tsla.csv";
		break;
	}
	cout << "Reading " << filename << endl;

	ifstream fin(filename);
	//vector<double> fields;
	double tmp = 0;
	string::size_type sz;
	int counter = 0;

	string line;
	while (getline(fin, line)) {
		istringstream sin(line);
		string field;

		while (getline(sin, field, ',') && counter <= n+1) {
			tmp = stod(field, &sz);
			//fields.push_back(tmp);
			td[counter] = tmp;
			counter++;
		}
	}
}

void CurveFitting::polynomial(int n)
{
	//each row is the polynimal of one x
	//but after map it to matrix, each column is matrix is the polynimal of one x
	for (int i = 0; i < n; i++)
		for (int j = 0; j < M + 1; j++)
			poly[i][j] = pow(i + 1, j);
}

void CurveFitting::print(int n)
{
	for (int i = 0; i < n; i++)
		cout << td[i] << ",";
}

void CurveFitting::curvefitting(int n)
{
	/* matrix of polynomial*/
	Map<MatrixXd> P(*poly, M + 1, n);
	//cout << "Poly is:" << endl;
	//cout << P << endl;

	/* sum of vector phi(x) */
	double sumS[10][10] = { 0 };
	Map<MatrixXd> SumS(*sumS, M + 1, M + 1);
	VectorXd tmp(M + 1, 1);
	for (int i = 0; i < n; i++) {
		tmp = P.block(0, i, M + 1, 1);
		SumS += tmp*tmp.transpose();
	}
	//cout << "SumS is:" << endl;
	//cout << SumS << endl;

	/* matrix S */
	MatrixXd S(M + 1, M + 1);
	S = (ALPHA*(MatrixXd::Identity(M + 1, M + 1)) + BETA*SumS).inverse();
	//cout << "S is:" << endl << S << endl;

	/* mean of guassian distribution */
	double sumM[10] = { 0 };
	Map<VectorXd> SumM(sumM, M + 1, 1);
	for (int i = 0; i < n; i++) {
		tmp = P.block(0, i, M + 1, 1);
		SumM += tmp*td[i];
	}
	//cout << "SumM is:" << endl << SumM << endl;
	double px[10] = { 0 };
	for (int i = 0; i < M + 1; i++)
		px[i] = pow(n + 1, i);
	Map<VectorXd> Px(px, M + 1, 1);		//polynomial of the new x
	//cout << "Px is:" << endl << Px << endl;
	MatrixXd part_mean(1, 1);
	part_mean(0, 0) = 0;
	part_mean = Px.transpose()*S*SumM;
	mean = BETA * part_mean.coeffRef(0, 0);
	//cout << "Mean is: " << mean << endl;

	/* variance of guassian distribution */
	var = 1 / BETA + Px.transpose()*S*Px;
	
	/* calculate prediction distribution using guassian distribution */
	double exp_param = (-(1 / (2 * var*var)))*(n + 1 - mean)*(n + 1 - mean);
	pre_dist = 1 / pow(2 * 3.14*var*var, 0.5)*exp(exp_param);
}

double CurveFitting::getMean()
{
	return mean;
}

double CurveFitting::getVar()
{
	return var;
}

double CurveFitting::getDist()
{
	return pre_dist;
}

double CurveFitting::getPrice(int n)
{
	return td[n];
}

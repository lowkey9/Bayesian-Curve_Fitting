#include <iostream>
#include <math.h>
#include "CurveFitting.h"

using namespace std;

int main()
{
	int choice = 0;
	int N[10] = { 10, 20, 50, 80, 100, 120, 150, 180, 200, 250 };
	cout << "Choose a stock in the following list" << endl;
	cout << "1. aapl" << endl;
	cout << "2. baba" << endl;
	cout << "3. bac" << endl;
	cout << "4. f" << endl;
	cout << "5. fb" << endl;
	cout << "6. gld" << endl;
	cout << "7. goog" << endl;
	cout << "8. lng" << endl;
	cout << "9. msft" << endl;
	cout << "10. tsla" << endl;
	cin >> choice;
	//cout << endl << "Enter the number of training data" << endl;
	//cin >> N;

	for (int i = 0; i < 10; i++) {
		cout << "The following is for N:" << N[i] << endl;
		CurveFitting cf;
		cf.readFile(choice, N[i]);
		cf.polynomial(N[i]);

		cf.curvefitting(N[i]);

		double predict = cf.getMean();
		double actual = cf.getPrice(N[i]);
		double diff = fabs(predict - actual);
		cout << "Prediction is: " << predict << endl;
		cout << "Actual price is: " << actual << endl;
		cout << "Absolute value of difference is: " << diff << endl;
		cout << "Variance is: " << cf.getVar() << endl;
		cout << "Prediciton distribution is: " << cf.getDist() << endl;
	}
	return 0;
}

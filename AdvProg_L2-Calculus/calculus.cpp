#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
using namespace std;
double arithmetic(double num1, double num2, char op);
double CalFunc (string& func, double num);
int main(int argc, char* argv[])
{
	double num1, num2;
	char op;
	
	if (argc == 3) {
		string func = argv[1];
		double num = atof(argv[2]);
		cout << CalFunc(func, num) << endl;
		return 0;	
	}
	
	if (argc == 4) {
		num1 = atof(argv[1]);
		op = argv[2][0];
		num2 = atof(argv[3]);
	
		cout << arithmetic(num1, num2, op) << endl;
		return 0;
	}
}

double arithmetic(double num1, double num2, char op)
{
	
	switch (op) {
		case '+':
		return num1 + num2;
		
		case '-':
		return num1 - num2;
		
		case '*':
		case 'x':
		return num1 * num2;
		
		case '/':
		if (num2 == 0.0) {
			cout << "Invalid divisor" << endl;
			exit(1);
		}
		return num1 / num2;
		
		default:
		cout << "Invalid operator" << endl;
		exit(1);
	}
}

double CalFunc (string& func, double num) {
	if (func == "sqrt") { 
		if (num < 0) {
			cout << "Invalid input";
		}
		return sqrt(num);
	}

	if (func == "cos")	return cos(num);
	if (func == "sin") return sin(num);
	
	cout << "Invalid function";
	exit(1);
}

#include<iostream>
#include<stack>
#include<string>
#include<sstream>
#include<vector>
#include"custom_check.h"

using namespace std;

int main(int argc, char* argv[]) {
		string exp;
		string temp;
		stack<string> oprnd_stk;
		stack<string> oprtr_stk;

		cout << "Enter an expression: " << endl;
		//GEtting input with the delimiter
		getline(cin, temp);
		stringstream tempstream(temp);

		while (getline(tempstream, exp, ','))
		{
			//checking for operator
			if (isOperator(exp)) {
				if (oprtr_stk.empty())
				{
					oprtr_stk.push(exp);
					continue;
				}
				else {
					//Checking precedence
					if (isPrecedence(exp, oprtr_stk.top())) {
						oprtr_stk.push(exp);
						continue;
					}
					else {
						string op1, op2, op;
						op2 = oprtr_stk.top();
						oprtr_stk.pop();
						op1 = oprtr_stk.top();
						oprtr_stk.pop();
						op = oprnd_stk.top();
						oprtr_stk.pop();
						oprtr_stk.push(solve(op1, op, op2));
					}
				}
			}
			//checking for closing parenthesis
			if (exp == ")") {
				while (oprtr_stk.top() != "(") {
					string op1, op2, op;
					op2 = oprnd_stk.top();
					oprnd_stk.pop();
					op1 = oprnd_stk.top();
					oprnd_stk.pop();
					op = oprtr_stk.top();
					oprtr_stk.pop();
					oprnd_stk.push(solve(op1, op, op2));
				}
				oprtr_stk.pop();
				continue;
			}
			oprnd_stk.push(exp);
		}
		//evaluating the complete stack.
		while (!oprtr_stk.empty())
		{
			string op1, op2, op;
			op2 = oprnd_stk.top();
			oprnd_stk.pop();
			op1 = oprnd_stk.top();
			oprnd_stk.pop();
			op = oprtr_stk.top();
			oprtr_stk.pop();
			oprnd_stk.push(solve(op1, op, op2));
		}

		cout << "The Answer is: " << oprnd_stk.top() << endl;

	system("pause");
	return 0;
}
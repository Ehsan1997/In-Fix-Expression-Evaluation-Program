#include<string>
#include<stack>
#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

bool isComma(char check) {
	if (check == ',')
		return true;
	else
		return false;
}

void display_stack(stack<string> a) {
	while (!a.empty())
	{
		cout << a.top() << " ";
		a.pop();
	}
	cout << endl;
}

void display_stack(stack<string> a, bool b) {
	if (b)
	{
		string temp[100];
		int i = 0;
		while (!a.empty())
		{
			temp[i] = a.top();
			a.pop();
			i++;
		}
		i -= 1;
		for (i; i >= 0; i--)
		{
			cout << temp[i] << " ";
		}
		cout << endl;
	}
	else
	{
		display_stack(a);
	}
}

bool isOperator(string a) {
	if (a == "+" || a == "-" || a == "x" || a == "/" || a == "(") {
		return true;
	}
	else 
		return false;
}

bool isOperand(string a) {
	if (a == "+" || a == "-" || a == "x" || a == "/" || a == "(" || a == ")") {
		return false;
	}
	return true;
}

bool isPrecedence(string a, string b) {
	if ((b == "x" || b == "/") && (a == "+" || a == "-"))
		return false;
	return true;
}


string solve(string a, string s, string b) {
	int a_i = stoi(a), b_i = stoi(b);
	if (s == "+")
	{
		return to_string(a_i + b_i);
	}
	if (s == "-")
	{
		return to_string(a_i - b_i);
	}
	if (s == "x")
	{
		return to_string(a_i * b_i);
	}
	if (s == "/")
	{
		return to_string(a_i / b_i);
	}
}

string convert_in_post_fix(string temp) {
	string exp;
	string output;
	stack<string> stk;

	stringstream tempstream(temp);

	while (getline(tempstream, exp, ','))
	{
		if (isOperator(exp)) {
			if (stk.empty())
			{
				stk.push(exp);
				continue;
			}
			else {
				if (isPrecedence(exp, stk.top())) {
					stk.push(exp);
					continue;
				}
				else {
					output += exp;
					output += ",";
				}
			}
		}
		if (exp == ")") {
			while (stk.top() != "(") {
				output += stk.top();
				output += ",";
				stk.pop();
			}
			stk.pop();
			continue;
		}
		output += exp;
		output += ",";
	}

	while (!stk.empty())
	{
		output += stk.top();
		output += ",";
		stk.pop();
	}

	return output;
}

string solve_post_fix(string temp) {
	string exp;
	string output;
	stack<string> stk;
	stringstream tempstream(temp);

	while (getline(tempstream, exp, ','))
	{
		if (isOperand(exp)) {
			stk.push(exp);
		}
		if (isOperator(exp)) {
			string b = stk.top();
			stk.pop();
			string a = stk.top();
			stk.pop();
			output = solve(a, exp, b);
			stk.push(output);
		}
	}

	return stk.top();

}
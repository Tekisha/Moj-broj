#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>


template <typename T>
class Calculator {
public:
	T Calculate(T operand1, T operand2, char op) {
		switch (op) {
		case '+': return operand1 + operand2;
		case '-': return operand1 - operand2;
		case '*': return operand1 * operand2;
		case '/': return operand1 / operand2;
		default:
			std::cerr << "Invalid operator: " << op << std::endl;
			return 0;
		}
	}
};

template <typename T>
inline T evaluateExpression(const std::string& expr)
{
	std::stack<T> operands;

	for (int i = 0; i < expr.length(); ++i) {
		if (isdigit(expr[i])) {
			int num = 0;
			int j = i;
			while (j < expr.length() && isdigit(expr[j])) {
				num = num * 10 + (expr[j] - '0');
				j++;
			}
			i = j - 1;
			operands.push(num);
		}
		else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' ||
			expr[i] == '/') {
			T op1 = operands.top();
			operands.pop();
			T op2 = operands.top();
			operands.pop();

			/*std::cout << op1 << " " << op2 << std::endl;*/
			T res = 0;
			if (expr[i] == '+') res = op1 + op2;
			else if (expr[i] == '-') res = op2 - op1;
			else if (expr[i] == '*') res = op1 * op2;
			else if (expr[i] == '/') res = op2 / op1;
			operands.push(res);
		}
	}
	return operands.top();
}

void readFile(const std::string& filename, std::vector<std::vector<int>>& retVal); //cita podatke iz fajla
int evaluateExpression(const std::string& expr); //racuna izraz
int priority(char alpha); //vraca prioritet operacije
bool isValidExpression(const std::string& expr);//provjerava da li je uneti izraz ispravan
void playGame(); //pocetak  igre
std::string infix_to_postfix(const std::string& infix, std::vector<int> numbers); //izraz iz infixa u postfix
void printGivenNumbers(const std::vector<int>& numbers, const int& target); //ispis pocetka runde


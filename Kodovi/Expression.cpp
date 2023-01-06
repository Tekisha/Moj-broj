#include "Expression.h"

Expression::Expression() :expression(""), value(), valid(), num(), priority(), id(),
left(), right(), sign() {}

Expression::~Expression()
{
}

Expression::Expression(Expression& e1, Expression& e2, char op) :
	expression(), num(e1.num + e2.num), valid(), value(), left(&e1), right(&e2), sign(op), id(), priority()
{
	exprString();
	calculateValue();
	addIndex(e1, e2);
}

Expression::Expression(int n, int i) : expression(std::to_string(n)),
value(n), priority(0), num(1), id(), sign(0), left(), right(), valid()
{
	id.push_back(i);
}

void Expression::calculateValue()
{
	switch (sign) {
	case '+':
		value = left->value + right->value;
		priority = 1;
		break;
	case '-':
		this->value = left->value - right->value;
		this->priority = 1;
		break;
	case '*':
		value = left->value * right->value;
		priority = 2;
		break;
	case '/':
		value = left->value / right->value;
		priority = 2;
		break;
	}
}

void Expression::exprString()
{
	//ako je samo broj,onda nista ne radimo
	if (sign == 0) {
		return;
	}

	switch (sign) {
	case '+':
		//ako je plus samo spajamo izraze,jer je + najnizeg prioriteta
		expression = left->expression + "+" + right->expression;
		break;
	case '-':
		//ako je minus samo spajamo izraze,jer je - najnizeg prioriteta
		expression = left->expression + "-" + right->expression;
		break;
	case '*':
		//provjeravamo da li je nesto prioriteta 1 ili 0,
		//ako jeste stavljamo u zagradu jer ce se to prvo izracunati
		if (left->priority == 1) {
			expression += "(" + left->expression + ")" + "*";
		}
		else {
			expression += left->expression + "*";
		}

		if (right->priority == 1) {
			expression += "(" + right->expression + ")";
		}
		else {
			expression += right->expression;
		}
		break;
	case '/':
		// opet ako je nesto nizeg prioriteta od 2 stavljamo u zagradu
		// jer je taj izraz vec izracunat
		if (left->priority == 1) {
			expression += "(" + left->expression + ")" + "/";
		}
		else {
			expression += left->expression + "/";
		}

		//ovdje stavljamo i mnozenje u zagradu jer je taj dio vec izracunat 
		//predstavljajuci imenilac koji dijeli brojilac
		if (right->priority != 0) {
			expression += "(" + right->expression + ")";
		}
		else {
			expression += right->expression;
		}
		break;





	}

}

void Expression::addIndex(Expression& e1, Expression& e2)
{
	std::vector<int>::iterator itt;
	for (itt = e1.id.begin(); itt != e1.id.end(); ++itt) {
		this->id.push_back(*itt);
	}
	for (itt = e2.id.begin(); itt != e2.id.end(); ++itt) {
		if (std::find(e1.id.begin(), e1.id.end(), *itt) == e1.id.end()) {
			this->id.push_back(*itt);
		}
	}
}

bool Expression::operator<(Expression& e2)
{
	if (value > e2.value) {
		return true;
	}
	else if (value < e2.value) {
		return false;
	}
	if (num > e2.num) {
		return true;
	}
	else if (num < e2.num) {
		return false;
	}

	return true;

}

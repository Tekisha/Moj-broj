#pragma once
#include <iostream>
#include <vector>
#include "Expression.h"

class ExprGenerator {
public:
	int target; //broj koji zelimo da nadjemo
	bool found; //da li je tacna vrijednost pronadjena
	int minValue; //minimalna udaljenost od trazenog broja
	Expression bestExp; //najbolji pronadjen izraz
	std::vector<int> operands; //ponudjeni brojevi
	std::vector<Expression> exp1; //vektor svih izraza sa jednim operandom
	std::vector<Expression> exp2; //vektor svih izraza sa dva operanda
	std::vector<Expression> exp3; //vektor svih izraza sa tri operanda
	std::vector<Expression> exp4; //      -//-         sa cetiri operanda
	std::vector<Expression> exp5; //      -//-         sa pet operanada
	std::vector<Expression> exp6; //      -//-         sa svih sest operanada


	//konstruktori i destruktor
	ExprGenerator();
	ExprGenerator(int target, std::vector<int> numbers);
	~ExprGenerator();


	void reset(int newTarget, std::vector<int> numbers); // reset kad je nova runda
	void clearLists(); //kad je nova runda svi vektori se ciste
	void generateExpr(); //generise sve moguce izraze
	bool notCommonId(Expression& e1, Expression& e2); //provjerava da li izrazi imaju isti element
	std::string& printSolution(); //printa najbolje rjesenje

	bool newSolution(Expression& e); //provjerava da li je dobijeni izraz novo najbolje rjesenje
	void buildOpComb(); //pravi sve izraze sa jednim operandom
	void buildComb(std::vector<Expression>& e1, std::vector<Expression>& e2, std::vector<Expression>& e); //pravi nove izraze sa e1+e2 operanada


};
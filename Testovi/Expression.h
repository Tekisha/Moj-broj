#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


//Instanca Klase izraz predstavlja jedan od izraza koje generator izraza generise, moguce rjesenje
class Expression {
public:
	std::string expression; //string izraz
	double value; //vrijednost izraza
	bool valid; // ako je izraz ceo broj
	int num; //broj operanada izraza
	int priority; //prioritet operacije
	std::vector<int> id; //indeks iskoriscenih operanada
	//izrazi od kojih je nastao ovaj izraz
	Expression* left;
	Expression* right;
	//operacija
	char sign;

	//konstruktori i destruktor
	Expression();
	~Expression();
	Expression(Expression& e1, Expression& e2, char op);
	Expression(int n, int i);


	void calculateValue(); //racuna vrijednost izraza
	void exprString(); //pravi izraz od left i right izraza i znaka
	void addIndex(Expression& e1, Expression& e2); //dodaje operande koji se nalaze u izrazu

	bool operator<(Expression& e2); //ovo sam radio jer sam mislio da ce mi trebati za sortiranje


};

#include "Tests.h"


//Testovi za funkciju koja racuna vrijednost izraza
void TestCalculator()
{
	std::vector<std::string> input;
	std::vector<int> numbers;
	input.push_back("5+(9-5*3)*5");
	input.push_back("10/5+32-(15-9)/3");
	input.push_back("5*6*10-25*3*2");
	input.push_back("25-9-(8)+2");
	input.push_back("13*5-6/2+3");
	input.push_back("26+59+(59-3*2)*2");
	input.push_back("33-3*2+6");
	input.push_back("88/4*56/2");
	input.push_back("25*(25-15*2)");
	input.push_back("14+(23-12)*11");

	std::vector<std::string>::iterator itt;
	for (itt = input.begin(); itt != input.end(); ++itt) {
		std::cout << *itt << " = " << evaluateExpression<double>(infix_to_postfix(*itt, numbers)) << std::endl;
	}

}

//Testovi za generator izraza
void TestGenerator()
{
	ExprGenerator generator = ExprGenerator(253, std::vector<int> {1, 3, 4, 2, 15, 12});
	generator.generateExpr();
	generator.printSolution();
	std::cout << "Tacan rezultat = " << evaluateExpression<double>(infix_to_postfix(generator.bestExp.expression, std::vector<int> {}));

	generator.reset(999, std::vector<int>{ 3, 4, 7, 9, 19, 50 });
	generator.generateExpr();
	generator.printSolution();
	std::cout << "Tacan rezultat = " << evaluateExpression<double>(infix_to_postfix(generator.bestExp.expression, std::vector<int> {}));

	generator.reset(534, std::vector<int>{ 7, 8, 5, 9, 15, 75 });
	generator.generateExpr();
	generator.printSolution();
	std::cout << "Tacan rezultat = " << evaluateExpression<double>(infix_to_postfix(generator.bestExp.expression, std::vector<int> {}));

	generator.reset(256, std::vector<int>{ 7, 7, 2, 3, 20, 100 });
	generator.generateExpr();
	generator.printSolution();
	std::cout << "Tacan rezultat = " << evaluateExpression<double>(infix_to_postfix(generator.bestExp.expression, std::vector<int> {}));

	generator.reset(487, std::vector<int>{3, 7, 9, 5, 21, 50 });
	generator.generateExpr();
	generator.printSolution();
	std::cout << "Tacan rezultat = " << evaluateExpression<double>(infix_to_postfix(generator.bestExp.expression, std::vector<int> {}));




}

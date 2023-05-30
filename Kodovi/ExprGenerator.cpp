#include "ExprGenerator.h"

ExprGenerator::ExprGenerator() :target(),
found(), minValue(), bestExp(), operands(), exp1(), exp2(), exp3(), exp4(), exp5(), exp6()
{
}

ExprGenerator::ExprGenerator(int target, std::vector<int> numbers) :target(target),
found(false), minValue(1000000), bestExp(), operands(numbers), exp1(), exp2(), exp3(), exp4(), exp5(), exp6() {}

ExprGenerator::~ExprGenerator()
{
}

void ExprGenerator::reset(int newTarget, std::vector<int> numbers)
{
	target = newTarget;
	operands = numbers;
	minValue = 1000000;
	found = false;
	// provjeriti da li ovo radi
	bestExp = Expression();
	clearLists();
}

void ExprGenerator::clearLists()
{
	exp1.clear();
	exp2.clear();
	exp3.clear();
	exp4.clear();
	exp5.clear();
	exp6.clear();
}

void ExprGenerator::generateExpr()
{
	sort(operands.begin(), operands.end()); //lakse preskacemo iste slucajeve

	buildOpComb(); //kreiramo sve moguce kombinacije brojeva

	buildComb(exp1, exp1, exp2); // od vektora sa 1 operandom pravimo sve moguce sa 2 operanda
	if (found) {
		return;
	}
	buildComb(exp2, exp1, exp3); // od vektora sa 1 i 2 operanda pravimo sve moguce sa 3 operanda
	if (found) {
		return;
	}
	buildComb(exp3, exp1, exp4); //analogno 
	if (found) {
		return;
	}
	buildComb(exp2, exp2, exp4); //analogno 
	if (found) {
		return;
	}
	buildComb(exp4, exp1, exp5); //analogno 
	if (found) {
		return;
	}
	buildComb(exp3, exp2, exp5); //analogno 
	if (found) {
		return;
	}
	buildComb(exp5, exp1, exp6); //analogno 
	if (found) {
		return;
	}
	buildComb(exp4, exp2, exp6); //analogno 
	if (found) {
		return;
	}
	buildComb(exp3, exp3, exp6); //analogno 


}


bool ExprGenerator::notCommonId(Expression& e1, Expression& e2)
{
	std::vector<int>::iterator itt;
	for (itt = e2.id.begin(); itt != e2.id.end(); ++itt) {
		if (std::find(e1.id.begin(), e1.id.end(), *itt) != e1.id.end()) {
			return false;
		}
	}
	return true;
}

std::string& ExprGenerator::printSolution()
{
	std::cout << "\n Racunar: ";
	std::cout << bestExp.expression + " = " << bestExp.value << std::endl;
	return bestExp.expression;
}

bool ExprGenerator::newSolution(Expression& e)
{
	if (e.value == target) {
		if (minValue != 0) {
			bestExp = e;
			minValue = 0;
			found = true;
			return true;
		}
	}
	else if (abs(e.value - target) < minValue && ceil(e.value) == floor(e.value)) {
		minValue = abs(e.value - target);
		bestExp = e;

	}
	return false;
}

//void ExprGenerator::buildOpComb()
//{
//	std::vector<int>::iterator itt;
//	int i = 0;
//	for (itt = operands.begin(); itt != operands.end(); ++itt) {
//		Expression e = Expression(*itt, i);
//		exp1.push_back(e);
//		++i;
//
//		if (newSolution(e)) {
//			return;
//		}
//	}
//}
void ExprGenerator::buildOpComb()
{
	tbb::task_group_context ctx;
	tbb::parallel_for(tbb::blocked_range<size_t>(0, operands.size()),
		[&](const tbb::blocked_range<size_t>& range) {
			for (size_t i = range.begin(); i != range.end(); ++i) {
				Expression e = Expression(operands[i], static_cast<int>(i));
				exp1.push_back(e);

				if (newSolution(e)) {
					// Cancel the parallel execution if a solution is found
					ctx.cancel_group_execution();
				}
			}
		}, ctx
	);
}

void ExprGenerator::buildComb(std::vector<Expression>& e1, std::vector<Expression>& e2, std::vector<Expression>& e)
{
	if (found) {
		return;
	}
	int n1 = e1.at(0).num;
	int n2 = e2.at(0).num;
	for (int i = 0; i < e1.size(); ++i) {
		for (int j = 0; j < e2.size(); ++j) {
			Expression expression1 = e1.at(i);
			Expression expression2 = e2.at(j);
			if (!notCommonId(expression1, expression2)) {
				continue;
			}
			//ako su n1 i n2 jednaki to znaci da su e1 i e2 jednaki sto znaci 
			// da ako je prvi brojac i veci ili jednak od j da ce biti isti slucaj
			if ((n1 == n2) && (i >= j)) {
				continue;
			}

			Expression newExp;
			///////////////////////////////////////////////////////
			//A+B

			//uslov omogucava da prvo dodajemo + po +, bez razlike,koju cemo naknadno dodati
			//da ne bi doslo do ponavljanja slucajeva
			if ((expression1.sign != '-') && (expression2.priority != 1)) {
				newExp = Expression(expression1, expression2, '+');
				e.push_back(newExp);
				if (newSolution(newExp)) {
					return;
				}
			}
			////B+A
			//if ((expression2.sign != '-') && (expression1.priority != 1)) {
			//	newExp = Expression(expression1, expression2, '+');
			//	e.push_back(newExp);
			//	if (newSolution(newExp)) {
			//		return;
			//	}
			//}
			///////////////////////////////////////////////////////

			//A*B

			//isto kao i kod +, prvo dodajemo sve * pa onda / da ne bi doslo do ponavljanja 
			if (expression1.value != 1 && expression2.value != 1 && expression1.value != '/'
				&& expression2.priority != 2) {
				newExp = Expression(expression1, expression2, '*');
				e.push_back(newExp);
				if (newSolution(newExp)) {
					return;
				}
			}
			//B*A
			/*if (expression1.value != 1 && expression2.value != 1) {
				newExp = Expression(expression2, expression1, '*');
				e.push_back(newExp);
				if (newSolution(newExp)) {
					return;
				}
			}*/
			//A-B
			if (expression1.value > expression2.value) {
				newExp = Expression(expression1, expression2, '-');
				e.push_back(newExp);
				if (newSolution(newExp)) {
					return;
				}
				newExp = Expression(expression1, expression2, ')');
				e.push_back(newExp);
				if (newSolution(newExp)) {
					return;
				}
			}
			//B-A
			else if (expression1.value < expression2.value) {
				newExp = Expression(expression2, expression1, '-');
				e.push_back(newExp);
				if (newSolution(newExp)) {
					return;
				}
				newExp = Expression(expression2, expression1, ')');
				e.push_back(newExp);
				if (newSolution(newExp)) {
					return;
				}
			}
			//A/B
			if (expression2.value != 1 && expression1.value != 1) {
				newExp = Expression(expression1, expression2, '/');
				e.push_back(newExp);
				if (newSolution(newExp)) {
					return;
				}
				newExp = Expression(expression2, expression1, '/');
				e.push_back(newExp);
				if (newSolution(newExp)) {
					return;
				}
			}


		}
	}


}

void ExprGenerator::generateExprParallel()
{
	sort(operands.begin(), operands.end());

	buildOpComb();

	tbb::task_group g;

	g.run([&]() { buildCombParallel(exp1, exp1, exp2); });
	g.run([&]() { buildCombParallel(exp2, exp1, exp3); });
	g.run([&]() { buildCombParallel(exp3, exp1, exp4); });
	g.run([&]() { buildCombParallel(exp2, exp2, exp4); });
	g.run([&]() { buildCombParallel(exp4, exp1, exp5); });
	g.run([&]() { buildCombParallel(exp3, exp2, exp5); });
	g.run([&]() { buildCombParallel(exp5, exp1, exp6); });
	g.run([&]() { buildCombParallel(exp4, exp2, exp6); });
	g.run([&]() { buildCombParallel(exp3, exp3, exp6); });

	g.wait();
}

void ExprGenerator::buildCombParallel(std::vector<Expression>& e1,std::vector<Expression>& e2, std::vector<Expression>& e)
{
	std::vector<std::vector<Expression>> localExp(e1.size());

	tbb::parallel_for(tbb::blocked_range<int>(0, e1.size()),
		[&](const tbb::blocked_range<int>& range) {
			for (int i = range.begin(); i < range.end(); ++i) {
				buildComb(e1, e2, localExp[i]);
			}
		}
	);

	// Combine localExp vectors into a single vector
	for (const auto& localVec : localExp) {
		e.insert(e.end(), localVec.begin(), localVec.end());
	}
}
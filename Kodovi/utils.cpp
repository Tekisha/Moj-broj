#pragma once
#include "utils.h"
#include "ExprGenerator.h"


void readFile(const std::string& filename, std::vector<std::vector<int>>& retVal)
{
	std::vector<int> oneRound;
	std::string  line;

	std::fstream input;
	input.open(filename, std::ios::in);
	int i = 0;
	while (input >> line) {
		if (i < 6) {
			oneRound.push_back(std::stoi(line));
			i++;
		}
		else {
			oneRound.push_back(std::stoi(line));
			retVal.push_back(oneRound);
			oneRound.clear();
			i = 0;
		}
	}
	input.close();
}

//int evaluateExpression(const std::string& expr)
//{
//	std::stack<double> operands;
//	
//	for (int i = 0; i<expr.length(); ++i) {
//		if (isdigit(expr[i])) {
//			int num = 0;
//			int j = i;
//			while (j < expr.length() && isdigit(expr[j])) {
//				num = num * 10 + (expr[j] - '0');
//				j++;
//			}
//			i = j-1;
//			operands.push(num);
//		}
//		else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' ||
//			expr[i] == '/') {
//			double op1 = operands.top();
//			operands.pop();
//			double op2 = operands.top();
//			operands.pop();
//
//			/*std::cout << op1 << " " << op2 << std::endl;*/
//			double res = 0;
//			if (expr[i] == '+') res = op1 + op2;
//			else if (expr[i] == '-') res = op2 - op1;
//			else if (expr[i] == '*') res = op1 * op2;
//			else if (expr[i] == '/') res = op2 / op1;
//			operands.push(res);
//		}
//	}
//	return operands.top();
//}

int priority(char alpha) {
	if (alpha == '+' || alpha == '-')
		return 1;

	if (alpha == '*' || alpha == '/')
		return 2;

	return 0;
}

bool isValidExpression(const std::string& expr)
{

	std::stack<char> zagrade;
	bool znak = false;

	if (expr == "") {
		return false;
	}

	if (expr[0] == '*' || expr[0] == '/' || expr[0] == '+' || expr[0] == '-') {
		std::cout << "Unos nije validan." << std::endl;
		return false;
	}

	if (expr[expr.length() - 1] == '*' || expr[expr.length() - 1] == '/' || expr[expr.length() - 1] == '+' || expr[expr.length() - 1] == '-') {
		std::cout << "Unos nije validan." << std::endl;
		return false;
	}

	for (int i = 0; i < expr.length(); i++) {
		if (i < expr.length() - 1) {
			if ((expr[i] == '(' && expr[i + 1] == '+') ||
				(expr[i] == '+' && expr[i + 1] == ')')) {
				std::cout << "Unos nije validan." << std::endl;
				return false;
			}
		}
		//provjera validnosti zagrada
		if (expr[i] == '(') {
			if (i < expr.length() - 1) {
				zagrade.push(expr[i]);
				znak = false;
			}
			else {
				std::cout << "Unos nije validan." << std::endl;
				return false;
			}
		}
		else if (expr[i] == ')') {
			if (zagrade.empty() || zagrade.top() != '(') {
				std::cout << "Raspored zagrada nije validan." << std::endl;
				return false;
			}
			else {
				zagrade.pop();
			}
			znak = false;
		}
		else if (isdigit(expr[i])) {
			znak = false;
		}
		else if (expr[i] == ' ') {
			std::cout << "Nije dozvoljeno unijeti prazan karakter." << std::endl;
			return false;
		}
		else if (!isdigit(expr[i]) && expr[i] != '+' && expr[i] != '-' &&
			expr[i] != '*' && expr[i] != '/' && expr[i] != '(' && expr[i] != ')') {
			std::cout << "Unijeli ste nedozvoljen karakter." << std::endl;
			return false;
		}
		else if ((expr[i] == '+' || expr[i] == '-' ||
			expr[i] == '*' || expr[i] == '/') && expr.length() == 1) {
			std::cout << "Unos nije validan." << std::endl;
			return false;
		}
		else if (expr[i] == '+' || expr[i] == '-' ||
			expr[i] == '*' || expr[i] == '/') {
			if (znak) {
				std::cout << "Unos nije validan." << std::endl;
				return false;
			}
			znak = true;
		}
	}
	return true;
}

void playGame()
{
	std::vector<std::vector<int>> inputData;
	readFile("input.txt", inputData);

	std::ofstream output;
	output.open("Rezultati.txt");


	std::vector<int> numbers; //vektor koji sadrzi ponudjene operande
	int target; //trazeni broj
	std::string userExpr; //izraz koji je unio takmicar
	int minDifB; //minimalna razlika izmedju rjesenja i broja takmicara
	int minDifA;
	double valueOfExp; //vrijednost unesenog izraza
	int roundsB = 0; //broj osvojenih rundi takmicara
	int roundsA = 0;

	ExprGenerator generator = ExprGenerator(); //generator izraza

	for (int i = 0; i < inputData.size(); ++i) {
		//da li igrac zeli da nastavi igru
		if (i != 0) {
			std::cout << "\n -----> Ako zelite zavrsiti igru unesite Q,ostalo za nastavak: ";
			std::string ans;
			std::cin >> ans;
			if (ans == "Q" || ans == "q") {
				break;
			}
		}
		output << "////////////////////////////////////////////////////////////////////" << std::endl;
		output << "Runda " << i + 1 << std::endl;
		// ucitavanje brojeva u novoj rundi
		numbers.clear();

		output << "Ponudjeni brojevi: ";
		for (int j = 0; j < inputData[i].size() - 1; ++j) {
			numbers.push_back(inputData[i][j]);
			output << inputData[i][j] << " ";
		}
		output << std::endl;

		sort(numbers.begin(), numbers.end()); // sortiramo brojeve da bi lakse provjerili da li je ispravan unos

		target = inputData[i][6];
		output << "Trazeni broj: " << target << std::endl;
		//////////////////////////////////////

		std::cout << "\n///////////////////////// Runda " << i + 1 << " ///////////////////////////" << std::endl;
		printGivenNumbers(numbers, target);
		//resetuje se generator
		generator.reset(target, numbers);

		//unos izraza i racunanje
		if ((i + 1) % 2 == 0) {
			userExpr = "";

			while (!isValidExpression(userExpr)) {
				std::cout << "Igrac B na potezu: " << std::endl;
				std::cin >> userExpr;
			}
			output << "Igrac B: " << userExpr << std::endl;


			userExpr = infix_to_postfix(userExpr, numbers);
			if (userExpr == "") {
				std::cout << "Mozete koristiti samo ponudjene brojeve. :(" << std::endl;
				std::cout << "Igrac A je osvojio rundu." << std::endl;
				output << "Igrac B nije koristio samo ponudjene brojeve. Igrac A osvojio rundu." << std::endl;
				roundsA++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}


			valueOfExp = evaluateExpression<double>(userExpr);
			if (ceil(valueOfExp) != floor(valueOfExp)) {
				std::cout << "Rezultat mora biti cijeli broj. :(" << std::endl;
				std::cout << "Igrac A je osvojio rundu." << std::endl;
				output << "Igrac B nije imao cjelobrojno resenje. Igrac A osvojio rundu." << std::endl;
				roundsA++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}
			std::cout << " = " << ceil(valueOfExp) << std::endl;
			output << "Vrednost izraza: " << valueOfExp << std::endl;

			minDifB = abs(target - valueOfExp);

			if (minDifB == 0) {
				std::cout << "Igrac B je nasao tacan broj. \n" << std::endl;
				output << "Igrac B je nasao tacan broj. Osvojio je rundu." << std::endl;
				roundsB++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}
			output << "Udaljenost: " << minDifB << std::endl << std::endl;
			/////////////////////////////////////////////////
			userExpr = "";

			while (!isValidExpression(userExpr)) {
				std::cout << "Igrac A na potezu: " << std::endl;
				std::cin >> userExpr;
			}
			output << "Igrac A: " << userExpr << std::endl;

			userExpr = infix_to_postfix(userExpr, numbers);
			if (userExpr == "") {
				std::cout << "Mozete koristiti samo ponudjene brojeve. :(" << std::endl;
				std::cout << "Igrac B je osvojio rundu." << std::endl;
				output << "Igrac A nije koristio samo ponudjene brojeve. Igrac B osvojio rundu." << std::endl;
				roundsB++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}

			valueOfExp = evaluateExpression<double>(userExpr);
			if (ceil(valueOfExp) != floor(valueOfExp)) {
				std::cout << "Rezultat mora biti cijeli broj. :(" << std::endl;
				std::cout << "Igrac B je osvojio rundu." << std::endl;
				output << "Igrac A nije imao cjelobrojno resenje. Igrac B osvojio rundu." << std::endl;
				roundsB++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}
			std::cout << " = " << ceil(valueOfExp) << std::endl;
			output << "Vrednost izraza: " << valueOfExp << std::endl;

			minDifA = abs(target - valueOfExp);
			output << "Udaljenost: " << minDifA << std::endl << std::endl;

			if (minDifA == 0) {
				std::cout << "Igrac A je nasao tacan broj. \n" << std::endl;
				output << "Igrac A je nasao tacan broj. Osvojio je rundu." << std::endl;
				roundsA++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}
			else if (minDifA < minDifB) {
				std::cout << "Igrac A je osvojio rundu." << std::endl;
				output << "Igrac A je osvojio rundu." << std::endl;
				roundsA++;
			}
			else {
				std::cout << "Igrac B je osvojio rundu." << std::endl;
				output << "Igrac B je osvojio rundu" << std::endl;
				roundsB++;
			}

		}
		else {
			userExpr = "";

			while (!isValidExpression(userExpr)) {
				std::cout << "Igrac A na potezu: " << std::endl;
				std::cin >> userExpr;
			}
			output << "Igrac A: " << userExpr << std::endl;

			userExpr = infix_to_postfix(userExpr, numbers);
			if (userExpr == "") {
				std::cout << "Mozete koristiti samo ponudjene brojeve. :(" << std::endl;
				std::cout << "Igrac B je osvojio rundu." << std::endl;
				output << "Igrac A nije koristio samo ponudjene brojeve. Igrac B osvojio rundu." << std::endl;
				roundsB++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}

			valueOfExp = evaluateExpression<double>(userExpr);
			if (ceil(valueOfExp) != floor(valueOfExp)) {
				std::cout << "Rezultat mora biti cijeli broj. :(" << std::endl;
				std::cout << "Igrac B je osvojio rundu." << std::endl;
				output << "Igrac A nije imao cjelobrojno resenje. Igrac B osvojio rundu." << std::endl;
				roundsB++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}
			std::cout << " = " << ceil(valueOfExp) << std::endl;
			output << "Vrednost izraza: " << valueOfExp << std::endl;

			minDifA = abs(target - valueOfExp);
			output << "Udaljenost: " << minDifA << std::endl << std::endl;

			if (minDifA == 0) {
				std::cout << "Igrac A je nasao tacan broj. \n" << std::endl;
				output << "Igrac A je nasao tacan broj. Osvojio je rundu." << std::endl;
				roundsA++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}
			/////////////////////////////////////////////////
			userExpr = "";

			while (!isValidExpression(userExpr)) {
				std::cout << "Igrac B na potezu: " << std::endl;
				std::cin >> userExpr;
			}
			output << "Igrac B: " << userExpr << std::endl;

			userExpr = infix_to_postfix(userExpr, numbers);
			if (userExpr == "") {
				std::cout << "Mozete koristiti samo ponudjene brojeve. :(" << std::endl;
				std::cout << "Igrac A je osvojio rundu." << std::endl;
				output << "Igrac B nije koristio samo ponudjene brojeve. Igrac A osvojio rundu." << std::endl;
				roundsA++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}

			valueOfExp = evaluateExpression<double>(userExpr);
			if (ceil(valueOfExp) != floor(valueOfExp)) {
				std::cout << "Rezultat mora biti cijeli broj. :(" << std::endl;
				std::cout << "Igrac A je osvojio rundu." << std::endl;
				output << "Igrac B nije imao cjelobrojno resenje. Igrac A osvojio rundu." << std::endl;
				roundsA++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}
			std::cout << " = " << ceil(valueOfExp) << std::endl;
			output << "Vrednost izraza: " << valueOfExp << std::endl;

			minDifB = abs(target - valueOfExp);
			output << "Udaljenost: " << minDifB << std::endl << std::endl;

			if (minDifB == 0) {
				std::cout << "Igrac B je nasao tacan broj. \n" << std::endl;
				output << "Igrac B je nasao tacan broj. Osvojio je rundu." << std::endl;
				roundsB++;
				//racunar pronalazi svoje rjesenje
				generator.generateExpr();
				output << "Racunar: " << generator.printSolution() << std::endl;
				continue;
			}
			else if (minDifB < minDifA) {
				std::cout << "Igrac B je osvojio rundu." << std::endl;
				output << "Igrac B je osvojio rundu." << std::endl;
				roundsB++;
			}
			else {
				std::cout << "Igrac A je osvojio rundu." << std::endl;
				output << "Igrac A je osvojio rundu." << std::endl;
				roundsA++;
			}

		}


		//racunar pronalazi svoje rjesenje
		generator.generateExpr();
		output << "Racunar: " << generator.printSolution() << std::endl;

	}
	std::cout << "///////////////////////////KRAJ IGRE////////////////////////////////" << std::endl;
	output << "///////////////////////////KRAJ IGRE////////////////////////////////" << std::endl;

	std::cout << "Igrac A: " << roundsA << " runde" << std::endl;
	output << "Igrac A: " << roundsA << " runde" << std::endl;

	std::cout << "Igrac B: " << roundsB << " runde" << std::endl;
	output << "Igrac B: " << roundsB << " runde" << std::endl;

	if (roundsA > roundsB) {
		std::cout << "Igrac A je pobijedio." << std::endl;
		output << "Igrac A je pobijedio." << std::endl;
	}
	else if (roundsB > roundsA) {
		std::cout << "Igrac B je pobijedio." << std::endl;
		output << "Igrac B je pobijedio." << std::endl;
	}
	else {
		std::cout << "Nerjeseno." << std::endl;
		output << "Nerjeseno." << std::endl;
	}

	output.close();
}

std::string infix_to_postfix(const std::string& infix, std::vector<int> numbers)
{

	std::vector<int> userNumbers;
	std::stack<int> stack;
	std::string output;

	for (int i = 0; i < infix.length(); ++i) {
		if (isdigit(infix[i])) {
			int num = 0;
			int j = i;
			while (j < infix.length() && isdigit(infix[j])) {
				num = num * 10 + (infix[j] - '0');
				j++;
			}
			output += std::to_string(num) + " ";
			userNumbers.push_back(num);
			i = j - 1;
		}
		else if (infix[i] == '(') {
			stack.push(infix[i]);
		}
		else if (infix[i] == ')') {
			while (stack.top() != '(') {
				output += stack.top();
				stack.pop();
			}
			stack.pop();
		}
		else {
			while (!stack.empty() && priority(infix[i]) <= priority(stack.top())) {
				output += stack.top();
				stack.pop();
			}
			stack.push(infix[i]);
		}

	}

	while (!stack.empty()) {
		output += stack.top();
		stack.pop();
	}

	//uslov ako je test
	if (numbers.size() == 0) {
		return output;
	}

	if (userNumbers.size() > numbers.size()) {
		return "";
	}
	sort(userNumbers.begin(), userNumbers.end());
	std::vector<int>::iterator itt;
	for (itt = userNumbers.begin(); itt != userNumbers.end(); ++itt) {
		auto location = std::find(numbers.begin(), numbers.end(), *itt);
		if (location == numbers.end()) {
			return "";
		}
		numbers.erase(location);

	}
	return output;
}

void printGivenNumbers(const std::vector<int>& numbers, const int& target)
{
	std::cout << "Trazeni broj : " << target << "\n" << std::endl;
	std::cout << "Ponudjeni brojevi: ";
	for (int i = 0; i < numbers.size(); ++i) {
		std::cout << numbers[i] << "  ";
	}
	std::cout << std::endl;
}


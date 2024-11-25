#include "Tree.h"
#include <Windows.h>


int main() {
	SetConsoleOutputCP(1251);
	int choice = 0;
	Tree root = nullptr;
	while (choice != 5) {
		std::cout << "\nМеню\n";
		std::cout << "1. Заполнить дерево из файла\n";
		std::cout << "2. Распечатать дерево\n";
		std::cout << "3. Найти производную\n";
		std::cout << "4. Удалить дерево\n";
		std::cout << "5. Выход\n";
		std::cout << "Введите пункт меню -> ";
		std::cin >> choice;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Введите корректный пункт меню\n";
			continue;
		}
		if (choice == 5) break;  // Выход из программы
		std::string expression;
		int pos = 0;
		int depth = 0;
		switch (choice) {
		case 1: {
			// Заполнение дерева из файла
			std::ifstream file("formula.txt");
			if (!file.is_open()) {
				std::cout << "Не удалось открыть файл!" << std::endl;
				break;
			}
			std::getline(file, expression);
			file.close();
			if (expression.empty()) {
				std::cout << "Файл пуст или не содержит выражения!" << std::endl;
				break;
			}
			root = parseExpression(expression, pos);
			if (root == nullptr) {
				std::cout << "Ошибка парсинга выражения!" << std::endl;
			}
			else {
				std::cout << "Дерево выражения заполнено" << std::endl;
			}
			break;
		}
		case 2: {
			// Печать дерева
			if (root != nullptr) {
				printTree(root, depth);
			}
			else {
				std::cout << "Дерево ещё не заполнено." << std::endl;
			}
			break;
		}
		case 3: {
			// Печать дерева в виде формулы
			if (root != nullptr) {
				char var;
				std::cout << "Введите переменную -> ";
				std::cin >> var;
				printTree(derivative(root, var), depth);
			}
			else {
				std::cout << "Дерево ещё не заполнено." << std::endl;
			}
			break;
		}
		case 4: {
			if (root != nullptr) {
				deleteTree(root);
				root = nullptr;
				std::cout << "Дерево удалено." << std::endl;
			}
			else {
				std::cout << "Нечего удалять, дерево не заполнено." << std::endl;
			}
			break;
		}
		default: {
			std::cout << "Введите корректный пункт меню\n";
			break;
		}
		}
	}

	if (root != nullptr) {
		deleteTree(root);
	}
	return 0;
}

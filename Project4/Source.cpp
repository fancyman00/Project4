#include "Tree.h"
#include <Windows.h>


int main() {
	SetConsoleOutputCP(1251);
	int choice = 0;
	Tree root = nullptr;
	while (choice != 5) {
		std::cout << "\n����\n";
		std::cout << "1. ��������� ������ �� �����\n";
		std::cout << "2. ����������� ������\n";
		std::cout << "3. ����� �����������\n";
		std::cout << "4. ������� ������\n";
		std::cout << "5. �����\n";
		std::cout << "������� ����� ���� -> ";
		std::cin >> choice;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "������� ���������� ����� ����\n";
			continue;
		}
		if (choice == 5) break;  // ����� �� ���������
		std::string expression;
		int pos = 0;
		int depth = 0;
		switch (choice) {
		case 1: {
			// ���������� ������ �� �����
			std::ifstream file("formula.txt");
			if (!file.is_open()) {
				std::cout << "�� ������� ������� ����!" << std::endl;
				break;
			}
			std::getline(file, expression);
			file.close();
			if (expression.empty()) {
				std::cout << "���� ���� ��� �� �������� ���������!" << std::endl;
				break;
			}
			root = parseExpression(expression, pos);
			if (root == nullptr) {
				std::cout << "������ �������� ���������!" << std::endl;
			}
			else {
				std::cout << "������ ��������� ���������" << std::endl;
			}
			break;
		}
		case 2: {
			// ������ ������
			if (root != nullptr) {
				printTree(root, depth);
			}
			else {
				std::cout << "������ ��� �� ���������." << std::endl;
			}
			break;
		}
		case 3: {
			// ������ ������ � ���� �������
			if (root != nullptr) {
				char var;
				std::cout << "������� ���������� -> ";
				std::cin >> var;
				printTree(derivative(root, var), depth);
			}
			else {
				std::cout << "������ ��� �� ���������." << std::endl;
			}
			break;
		}
		case 4: {
			if (root != nullptr) {
				deleteTree(root);
				root = nullptr;
				std::cout << "������ �������." << std::endl;
			}
			else {
				std::cout << "������ �������, ������ �� ���������." << std::endl;
			}
			break;
		}
		default: {
			std::cout << "������� ���������� ����� ����\n";
			break;
		}
		}
	}

	if (root != nullptr) {
		deleteTree(root);
	}
	return 0;
}

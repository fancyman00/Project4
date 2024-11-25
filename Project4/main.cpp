#include "TTREE.h"
//�� Trie ������ ������� ��� ����� ������������ � �������� ������������������ ����
short menu();

int main() {
	setlocale(LC_ALL, "Russian");
	TrieNode* root = createNode();
	int choice;
	std::string word, filename;
	int len;

	do {

		choice = menu();

		switch (choice) {
		case 1:
			loadFromFile(root, "data.txt");
			break;
		case 2:
			std::cout << "������� �����: ";
			std::cin >> word;
			insertWord(root, word);
			break;
		case 3:
			std::cout << "������� ����� ��� ��������: ";
			std::cin >> word;
			if (search(root, word)) {
				if (remove(root, word)) {
					std::cout << "����� �������." << std::endl;
				}
			}
			else {
				std::cout << "����� �� �������." << std::endl;
			}
			break;
		case 4:
			std::cout << "������� ����� ��� ������: ";
			std::cin >> word;
			if (search(root, word)) {
				std::cout << "����� �������." << std::endl;
			}
			else {
				std::cout << "����� �� �������." << std::endl;
			}
			break;
		case 5:
			clear(root);
			root = createNode();
			std::cout << "��� ����� �������." << std::endl;
			break;
		case 6:
			std::cout << "�����:" << std::endl;
			printAll(root);
			break;
		case 7: {
			std::cout << "������� ������ -> ";
			std::cin >> len;
			std::cout << std::endl << "������ ������" << std::endl;
			printAll(root);
			if (task(root, len)) {
				std::cout << std::endl << "����� � ��������� '" << word << "' �������" << std::endl;
				std::cout << std::endl << "����� ������" << std::endl;
				printAll(root);
				std::cout << std::endl;
			}
			else std::cout << "����� �� �������" << std::endl;
			break;
		}
		case 8:
			clear(root);
			delete root;
			std::cout << "�����." << std::endl;
			break;
		default:
			std::cout << "�������� �����!" << std::endl;
		}
	} while (choice != 8);

	return 0;
}

short menu() {
	short choice;
	std::cout << "1. ��������� �� �����" << std::endl;
	std::cout << "2. �������� ����� � ����������" << std::endl;
	std::cout << "3. ������� �����" << std::endl;
	std::cout << "4. ��������� ��������� �����" << std::endl;
	std::cout << "5. ������� ��� �����" << std::endl;
	std::cout << "6. �������� ��� �����" << std::endl;
	std::cout << "7. ������� ����� ������ �������� �����" << std::endl;
	std::cout << "8. �����" << std::endl;
	std::cout << "�������� ��������: ";
	std::cin >> choice;
	return choice;
}
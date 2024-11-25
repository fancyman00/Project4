#include "TTREE.h"
//Из Trie дерева удалить все слова начинающиеся с заданной последовательности букв
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
			std::cout << "Введите слово: ";
			std::cin >> word;
			insertWord(root, word);
			break;
		case 3:
			std::cout << "Введите слово для удаления: ";
			std::cin >> word;
			if (search(root, word)) {
				if (remove(root, word)) {
					std::cout << "Слово удалено." << std::endl;
				}
			}
			else {
				std::cout << "Слово не найдено." << std::endl;
			}
			break;
		case 4:
			std::cout << "Введите слово для поиска: ";
			std::cin >> word;
			if (search(root, word)) {
				std::cout << "Слово найдено." << std::endl;
			}
			else {
				std::cout << "Слово не найдено." << std::endl;
			}
			break;
		case 5:
			clear(root);
			root = createNode();
			std::cout << "Все слова удалены." << std::endl;
			break;
		case 6:
			std::cout << "Слова:" << std::endl;
			printAll(root);
			break;
		case 7: {
			std::cout << "Введите длинну -> ";
			std::cin >> len;
			std::cout << std::endl << "Старое дерево" << std::endl;
			printAll(root);
			if (task(root, len)) {
				std::cout << std::endl << "Слова с префиксом '" << word << "' удалены" << std::endl;
				std::cout << std::endl << "Новое дерево" << std::endl;
				printAll(root);
				std::cout << std::endl;
			}
			else std::cout << "Слова не найдены" << std::endl;
			break;
		}
		case 8:
			clear(root);
			delete root;
			std::cout << "Выход." << std::endl;
			break;
		default:
			std::cout << "Неверный выбор!" << std::endl;
		}
	} while (choice != 8);

	return 0;
}

short menu() {
	short choice;
	std::cout << "1. Загрузить из файла" << std::endl;
	std::cout << "2. Добавить слово с клавиатуры" << std::endl;
	std::cout << "3. Удалить слово" << std::endl;
	std::cout << "4. Проверить вхождение слова" << std::endl;
	std::cout << "5. Удалить все слова" << std::endl;
	std::cout << "6. Показать все слова" << std::endl;
	std::cout << "7. Удалить слова больше заданной длины" << std::endl;
	std::cout << "8. Выход" << std::endl;
	std::cout << "Выберите действие: ";
	std::cin >> choice;
	return choice;
}
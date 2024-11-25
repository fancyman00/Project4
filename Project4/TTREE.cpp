#include "TTREE.h"

TrieNode* createNode() {
	TrieNode* node = new TrieNode();
	return node;
}

int charToIndex(char ch)
{
	return tolower(ch - 'a');
}

void insertWord(TrieNode* root, const std::string& word)
{
	TrieNode* current = root;
	for (char ch : word) {
		int index = charToIndex(ch);
		if (!current->children[index]) {
			current->children[index] = createNode();
		}
		current = current->children[index];
	}
	current->isEndOfWord = true;
}

bool isEmpty(TrieNode* node)
{
	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		if (node->children[i] != nullptr)
			return false;
	}
	return true;
}

bool search(TrieNode* root, const std::string& word) {
	TrieNode* current = root;
	for (char ch : word) {
		int index = charToIndex(ch);
		if (index < 0 || index >= ALPHABET_SIZE) {
			std::cerr << "Некорректный символ: " << ch << std::endl;
			return false;
		}
		if (!current->children[index]) {
			return false;  // Если текущий символ не найден
		}
		current = current->children[index];
	}
	return current != nullptr && current->isEndOfWord;
}

bool remove(TrieNode* node, const std::string& word, int depth) {

	if (!node) return false;


	if (depth == word.size()) {
		if (!node->isEndOfWord) return false;
		node->isEndOfWord = false;
		return isEmpty(node);
	}

	int index = charToIndex(word[depth]);
	if (index < 0 || index >= ALPHABET_SIZE) {
		std::cout << "Некорректный символ: " << word[depth] << std::endl;
		return false;
	}

	if (!node->children[index]) return false;

	bool shouldDeleteCurrentNode = remove(node->children[index], word, depth + 1);

	if (shouldDeleteCurrentNode) {
		delete node->children[index];
		node->children[index] = nullptr;
		return true;
	}
}

void clear(TrieNode* node)
{
	if (!node) return;
	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		if (node->children[i]) {
			clear(node->children[i]);
			delete node->children[i];
			node->children[i] = nullptr;
		}
	}
}

void printAllHelper(TrieNode* node, std::string& currentWord)
{
	if (!node) return;

	if (node->isEndOfWord)
		std::cout << currentWord << '\n';

	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		if (node->children[i]) {
			currentWord.push_back('a' + i);
			printAllHelper(node->children[i], currentWord);
			currentWord.pop_back();
		}
	}

}

void printAll(TrieNode* root)
{
	std::string word;
	printAllHelper(root, word);
}

void loadFromFile(TrieNode* root, const std::string& filename)
{
	std::string word;
	std::ifstream file(filename);
	if (!file.is_open()) std::cout << "Ошибка открытия файла\n";
	while (file >> word) {
		insertWord(root, word);
	}
	std::cout << "Дерево успешно заполнено\n";
	file.close();
}
bool deleteLongWordsHelper(TrieNode* node, std::string& currentWord, int maxLength, bool& wordDeleted) {
	if (!node) return false;

	// Если слово слишком длинное и заканчивается здесь, удаляем его
	if (currentWord.length() > maxLength - 1 && node->isEndOfWord) {
		remove(node, currentWord);
		wordDeleted = true;  // Устанавливаем флаг, что слово было удалено
	}

	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		if (node->children[i]) {
			currentWord.push_back('a' + i);
			deleteLongWordsHelper(node->children[i], currentWord, maxLength, wordDeleted);
			currentWord.pop_back();
		}
	}

	return wordDeleted;
}
bool task(TrieNode* root, int maxLength) {
	std::string word;
	bool wordDeleted = false;
	return deleteLongWordsHelper(root, word, maxLength, wordDeleted);
}
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

const int ALPHABET_SIZE = 256;

struct TrieNode {
	TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord;
	TrieNode() :isEndOfWord(false) {
		for (int i = 0; i < ALPHABET_SIZE; ++i) {
			children[i] = nullptr;
		}
	}
};

// Создание нового узла
TrieNode* createNode();

// Преобразование символа в индекс массива (от 'a' до 'z')
int charToIndex(char ch);

// Добавление слова в Trie
void insertWord(TrieNode* root, const std::string& word);

// Проверка, пустой ли узел (нет потомков)
bool isEmpty(TrieNode* node);

// Проверка вхождения слова
bool search(TrieNode* root, const std::string& word);

// Удаление слова
bool remove(TrieNode* node, const std::string& word, int depth = 0);

// Рекурсивное удаление всех узлов
void clear(TrieNode* node);

// Вспомогательная функция вывода всех слов
void printAllHelper(TrieNode* node, std::string& currentWord);

// Основная функция вывода всех слов
void printAll(TrieNode* root);

// Загрузка слов из файла
void loadFromFile(TrieNode* root, const std::string& filename);

//Задача
bool deleteLongWordsHelper(TrieNode* node, std::string& currentWord, int maxLength, bool& wordDeleted);

//Задача
bool task(TrieNode* root, int maxLength);
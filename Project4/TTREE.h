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

// �������� ������ ����
TrieNode* createNode();

// �������������� ������� � ������ ������� (�� 'a' �� 'z')
int charToIndex(char ch);

// ���������� ����� � Trie
void insertWord(TrieNode* root, const std::string& word);

// ��������, ������ �� ���� (��� ��������)
bool isEmpty(TrieNode* node);

// �������� ��������� �����
bool search(TrieNode* root, const std::string& word);

// �������� �����
bool remove(TrieNode* node, const std::string& word, int depth = 0);

// ����������� �������� ���� �����
void clear(TrieNode* node);

// ��������������� ������� ������ ���� ����
void printAllHelper(TrieNode* node, std::string& currentWord);

// �������� ������� ������ ���� ����
void printAll(TrieNode* root);

// �������� ���� �� �����
void loadFromFile(TrieNode* root, const std::string& filename);

//������
bool deleteLongWordsHelper(TrieNode* node, std::string& currentWord, int maxLength, bool& wordDeleted);

//������
bool task(TrieNode* root, int maxLength);
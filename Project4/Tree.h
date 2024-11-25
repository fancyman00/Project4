#pragma once
#include <iostream>
#include <string>
#include <fstream>


struct Node {
	char value;  // Либо оператор (+, -, *, /), либо терминал (переменная или цифра)
	Node* left;  // Левое поддерево (если есть)
	Node* right; // Правое поддерево (если есть)

	Node(char v, Node* l = nullptr, Node* r = nullptr) : value(v), left(l), right(r) {}
};
using Tree = Node*;

// Функция для рекурсивного удаления дерева
void deleteTree(Tree root);

// Функция для печати дерева
void printTree(Node* root, int depth);
// Функция для печати дерева в виде формулы
std::string printFormula(Tree root);

// Функция для обработки выражения без скобок на уровне операторов + и -
Tree parseExpression(const std::string& expression, int& pos);

// Функция для обработки переменных, цифр и выражений в скобках
Tree parseFactor(const std::string& expression, int& pos);

// Функция для обработки выражений с приоритетом операторов * и /
Tree parseTerm(const std::string& expression, int& pos);

// Функция для обработки переменных, чисел или выражений в скобках
Tree parseFactor(const std::string& expression, int& pos);

// Функция для нахождения 
Tree derivative(Tree root, char variable);
#pragma once
#include <iostream>
#include <string>
#include <fstream>


struct Node {
	char value;  // ���� �������� (+, -, *, /), ���� �������� (���������� ��� �����)
	Node* left;  // ����� ��������� (���� ����)
	Node* right; // ������ ��������� (���� ����)

	Node(char v, Node* l = nullptr, Node* r = nullptr) : value(v), left(l), right(r) {}
};
using Tree = Node*;

// ������� ��� ������������ �������� ������
void deleteTree(Tree root);

// ������� ��� ������ ������
void printTree(Node* root, int depth);
// ������� ��� ������ ������ � ���� �������
std::string printFormula(Tree root);

// ������� ��� ��������� ��������� ��� ������ �� ������ ���������� + � -
Tree parseExpression(const std::string& expression, int& pos);

// ������� ��� ��������� ����������, ���� � ��������� � �������
Tree parseFactor(const std::string& expression, int& pos);

// ������� ��� ��������� ��������� � ����������� ���������� * � /
Tree parseTerm(const std::string& expression, int& pos);

// ������� ��� ��������� ����������, ����� ��� ��������� � �������
Tree parseFactor(const std::string& expression, int& pos);

// ������� ��� ���������� 
Tree derivative(Tree root, char variable);
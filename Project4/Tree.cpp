#include "Tree.h"

// ������� ��� �������� ������
void deleteTree(Tree root) {
	if (!root) return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}
// ������� ��� ������ ������
void printTree(Node* root, int depth) {
	if (root == nullptr) return;

	// ������� �������� ������ ���������
	if (root->right) {
		printTree(root->right, depth + 1);
	}

	// �������� ������� ��� �������� ������ ����
	for (int i = 0; i < depth; ++i) {
		std::cout << "    ";
	}

	// �������� ������� �������� ����
	std::cout << root->value << std::endl;

	// ����� �������� ����� ���������
	if (root->left) {
		printTree(root->left, depth + 1);
	}
}

// ������� ��� ������ ������ � ���� �������
std::string printFormula(Tree root) {
	if (!root) return "";

	// ���� ��� �������� (���������� ��� �����)
	if (!root->left && !root->right) {
		return std::string(1, root->value);
	}

	// ���� ��� ��������, ������� ����� � ������ ����� � ���������� ����� ����
	std::string leftStr = printFormula(root->left);
	std::string rightStr = printFormula(root->right);

	return "(" + leftStr + " " + root->value + " " + rightStr + ")";
}


// ������� ��� ��������� ��������� � ����������� ���������� + � -
Tree parseExpression(const std::string& expression, int& pos) {
	// ������ ������ ����, ������� ����� ���� ����������, ������ ��� �������������
	Tree root = parseTerm(expression, pos);

	// ���������� ��������� ��������� �� ������ ���������� + � -
	while (pos < expression.size() && (expression[pos] == '+' || expression[pos] == '-')) {
		char op = expression[pos++];
		Tree rightNode = parseTerm(expression, pos); // ������ ������ �����
		root = new Node(op, root, rightNode); // ������� ����� ���� � ����������
	}

	return root;
}

// ������� ��� ��������� ��������� � ����������� ���������� * � /
Tree parseTerm(const std::string& expression, int& pos) {
	// ������ ������ ����, ������� ����� ���� ����������, ������ ��� �������������
	Tree root = parseFactor(expression, pos);

	// ���������� ��������� ��������� �� ������ ���������� * � /
	while (pos < expression.size() && (expression[pos] == '*' || expression[pos] == '/')) {
		char op = expression[pos++];
		Tree rightNode = parseFactor(expression, pos); // ������ ������ �����
		root = new Node(op, root, rightNode); // ������� ����� ���� � ����������
	}

	return root;
}

// ������� ��� ��������� ����������, ����� ��� ��������� � �������
Tree parseFactor(const std::string& expression, int& pos) {
	// ���������� �������
	while (pos < expression.size() && expression[pos] == ' ') pos++;

	if (pos >= expression.size()) {
		return nullptr;  // ���� ������ �����������
	}

	if (expression[pos] == '(') {
		pos++; // ���������� ����������� ������
		Tree root = parseExpression(expression, pos); // ������ ��������� ������ ������
		if (pos < expression.size() && expression[pos] == ')') {
			pos++; // ���������� ����������� ������
		}
		return root;
	}

	// ���� ��� ���������� ��� �����
	char value = expression[pos++];
	return new Node(value);
}

Tree derivative(Tree root, char var) {
    if (!root) return nullptr;

    // ���� ��� ����������, ���������� 1, ���� ��� ������ ����������
    if (root->value == var) {
        return new Node('1');  // ����������� �� ���������� �� ����� ���� = 1
    }

    // ���� ��� ��������� (����� ��� ��������� ����������), ���������� 0
    if (root->value != '+' && root->value != '-' && root->value != '*' && root->value != '/') {
        return new Node('0');  // ����������� �� ��������� = 0
    }

    // ������������ ���������: +, -, *, /
    if (root->value == '+') {
        // ����������� �� ����� � ����� �����������
        Tree leftDerivative = derivative(root->left, var);
        Tree rightDerivative = derivative(root->right, var);
        return new Node('+', leftDerivative, rightDerivative);
    }

    if (root->value == '-') {
        // ����������� �� �������� � �������� �����������
        Tree leftDerivative = derivative(root->left, var);
        Tree rightDerivative = derivative(root->right, var);
        return new Node('-', leftDerivative, rightDerivative);
    }

    if (root->value == '*') {
        // ������� ������������: (a * b)' = a' * b + a * b'
        Tree leftDerivative = derivative(root->left, var);
        Tree rightDerivative = derivative(root->right, var);
        Tree part1 = new Node('*', leftDerivative, root->right);
        Tree part2 = new Node('*', root->left, rightDerivative);
        return new Node('+', part1, part2);
    }

    if (root->value == '/') {
        // ������� ��������: (a / b)' = (b * a' - a * b') / b^2
        Tree leftDerivative = derivative(root->left, var);
        Tree rightDerivative = derivative(root->right, var);
        Tree part1 = new Node('*', root->right, leftDerivative);
        Tree part2 = new Node('*', root->left, rightDerivative);
        Tree numerator = new Node('-', part1, part2);
        Tree denominator = new Node('*', root->right, root->right);
        return new Node('/', numerator, denominator);
    }

    // � ������ ������ ����� ������ (��������, ������), ���������� ��������� �����������
    if (root->left) {
        root->left = derivative(root->left, var);
    }
    if (root->right) {
        root->right = derivative(root->right, var);
    }

    return root;
}
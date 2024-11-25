#include "Tree.h"

// Функция для удаления дерева
void deleteTree(Tree root) {
	if (!root) return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}
// Функция для печати дерева
void printTree(Node* root, int depth) {
	if (root == nullptr) return;

	// Сначала печатаем правое поддерево
	if (root->right) {
		printTree(root->right, depth + 1);
	}

	// Печатаем отступы для текущего уровня узла
	for (int i = 0; i < depth; ++i) {
		std::cout << "    ";
	}

	// Печатаем текущее значение узла
	std::cout << root->value << std::endl;

	// Затем печатаем левое поддерево
	if (root->left) {
		printTree(root->left, depth + 1);
	}
}

// Функция для печати дерева в виде формулы
std::string printFormula(Tree root) {
	if (!root) return "";

	// Если это терминал (переменная или цифра)
	if (!root->left && !root->right) {
		return std::string(1, root->value);
	}

	// Если это оператор, выводим левую и правую части с оператором между ними
	std::string leftStr = printFormula(root->left);
	std::string rightStr = printFormula(root->right);

	return "(" + leftStr + " " + root->value + " " + rightStr + ")";
}


// Функция для обработки выражений с приоритетом операторов + и -
Tree parseExpression(const std::string& expression, int& pos) {
	// Парсим первый член, который может быть переменной, числом или подвыражением
	Tree root = parseTerm(expression, pos);

	// Продолжаем разбирать выражение на уровне операторов + и -
	while (pos < expression.size() && (expression[pos] == '+' || expression[pos] == '-')) {
		char op = expression[pos++];
		Tree rightNode = parseTerm(expression, pos); // Парсим правую часть
		root = new Node(op, root, rightNode); // Создаем новый узел с оператором
	}

	return root;
}

// Функция для обработки выражений с приоритетом операторов * и /
Tree parseTerm(const std::string& expression, int& pos) {
	// Парсим первый член, который может быть переменной, числом или подвыражением
	Tree root = parseFactor(expression, pos);

	// Продолжаем разбирать выражение на уровне операторов * и /
	while (pos < expression.size() && (expression[pos] == '*' || expression[pos] == '/')) {
		char op = expression[pos++];
		Tree rightNode = parseFactor(expression, pos); // Парсим правую часть
		root = new Node(op, root, rightNode); // Создаем новый узел с оператором
	}

	return root;
}

// Функция для обработки переменных, чисел или выражений в скобках
Tree parseFactor(const std::string& expression, int& pos) {
	// Пропускаем пробелы
	while (pos < expression.size() && expression[pos] == ' ') pos++;

	if (pos >= expression.size()) {
		return nullptr;  // Если строка закончилась
	}

	if (expression[pos] == '(') {
		pos++; // Пропускаем открывающую скобку
		Tree root = parseExpression(expression, pos); // Парсим выражение внутри скобок
		if (pos < expression.size() && expression[pos] == ')') {
			pos++; // Пропускаем закрывающую скобку
		}
		return root;
	}

	// Если это переменная или цифра
	char value = expression[pos++];
	return new Node(value);
}

Tree derivative(Tree root, char var) {
    if (!root) return nullptr;

    // Если это переменная, возвращаем 1, если это нужная переменная
    if (root->value == var) {
        return new Node('1');  // Производная от переменной по самой себе = 1
    }

    // Если это константа (цифра или буквенная переменная), возвращаем 0
    if (root->value != '+' && root->value != '-' && root->value != '*' && root->value != '/') {
        return new Node('0');  // Производная от константы = 0
    }

    // Обрабатываем операторы: +, -, *, /
    if (root->value == '+') {
        // Производная от суммы — сумма производных
        Tree leftDerivative = derivative(root->left, var);
        Tree rightDerivative = derivative(root->right, var);
        return new Node('+', leftDerivative, rightDerivative);
    }

    if (root->value == '-') {
        // Производная от разности — разность производных
        Tree leftDerivative = derivative(root->left, var);
        Tree rightDerivative = derivative(root->right, var);
        return new Node('-', leftDerivative, rightDerivative);
    }

    if (root->value == '*') {
        // Правило произведения: (a * b)' = a' * b + a * b'
        Tree leftDerivative = derivative(root->left, var);
        Tree rightDerivative = derivative(root->right, var);
        Tree part1 = new Node('*', leftDerivative, root->right);
        Tree part2 = new Node('*', root->left, rightDerivative);
        return new Node('+', part1, part2);
    }

    if (root->value == '/') {
        // Правило частного: (a / b)' = (b * a' - a * b') / b^2
        Tree leftDerivative = derivative(root->left, var);
        Tree rightDerivative = derivative(root->right, var);
        Tree part1 = new Node('*', root->right, leftDerivative);
        Tree part2 = new Node('*', root->left, rightDerivative);
        Tree numerator = new Node('-', part1, part2);
        Tree denominator = new Node('*', root->right, root->right);
        return new Node('/', numerator, denominator);
    }

    // В случае других типов данных (например, скобки), рекурсивно вычисляем производную
    if (root->left) {
        root->left = derivative(root->left, var);
    }
    if (root->right) {
        root->right = derivative(root->right, var);
    }

    return root;
}
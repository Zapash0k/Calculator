#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <map>
using namespace std;

// Функція для визначення пріоритету операції
int priorities(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Функція для виконання дії, переданої до функції
double applyOperation(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
    return 0;
}

// Основна функція для обчислення виразу
double calculations(string expression) {
    stack<double> values;  // Стек для чисел
    stack<char> ops;       // Стек для операторів

    for (int i = 0; i < expression.length(); i++) {
        // Пропускаємо пробіли
        if (isspace(expression[i]))
            continue;

        // Якщо це число, парсимо його
        if (isdigit(expression[i])) {
            double value = 0;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    i++;
                    double decimal_place = 0.1;
                    while (i < expression.length() && isdigit(expression[i])) {
                        value += (expression[i] - '0') * decimal_place;
                        decimal_place *= 0.1;
                        i++;
                    }
                    break;
                }
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            values.push(value);
            i--;  // Повертаємось на попередній символ для продовження циклу
        }
        // Якщо елемент є оператором
        else {
            while (!ops.empty() && priorities(ops.top()) >= priorities(expression[i])) {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOperation(val1, val2, op));
            }
            ops.push(expression[i]);
        }
    }

    // Виконуємо залишені операції
    while (!ops.empty()) {
        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOperation(val1, val2, op));
    }
    // Останній результат в стеку — відповідь, тож ми його і повертаємо
    return values.top();
}

int main() {
    string expression;
    cout << "Введіть приклад: "; // Запит на приклад для вирішення
    getline(cin, expression);
    double result = calculations(expression);  // Обчислення виразу
    cout << "Результат: " << result << endl;  // Виведення результату
    return 0;
}

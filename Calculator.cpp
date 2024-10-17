#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <map>
using namespace std;

// ������� ��� ���������� ��������� ��������
int priorities(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// ������� ��� ��������� 䳿, �������� �� �������
double applyOperation(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
    return 0;
}

// ������� ������� ��� ���������� ������
double calculations(string expression) {
    stack<double> values;  // ���� ��� �����
    stack<char> ops;       // ���� ��� ���������

    for (int i = 0; i < expression.length(); i++) {
        // ���������� ������
        if (isspace(expression[i]))
            continue;

        // ���� �� �����, ������� ����
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
            i--;  // ����������� �� ��������� ������ ��� ����������� �����
        }
        // ���� ������� � ����������
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

    // �������� ������� ��������
    while (!ops.empty()) {
        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOperation(val1, val2, op));
    }
    // ������� ��������� � ����� � �������, ��� �� ���� � ���������
    return values.top();
}

int main() {
    string expression;
    cout << "������ �������: "; // ����� �� ������� ��� ��������
    getline(cin, expression);
    double result = calculations(expression);  // ���������� ������
    cout << "���������: " << result << endl;  // ��������� ����������
    return 0;
}

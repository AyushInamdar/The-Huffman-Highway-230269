#include <iostream>
#include <cmath> // For basic math functions like log, sin, cos, tan, exp

// Function prototypes
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
int mod(int a, int b);
double ln(double x);
double sin_func(double x);
double cos_func(double x);
double tan_func(double x);
double exp_func(double x);

int main() {
    int numOperators;
    std::cout << "Enter the number of operators: ";
    std::cin >> numOperators;

    std::string operators[numOperators];
    std::cout << "Enter the operators (e.g., +, -, *, /, %, ln, sin, cos, tan, exp): ";
    for (int i = 0; i < numOperators; ++i) {
        std::cin >> operators[i];
    }

    double x;
    std::cout << "Enter the initial value of X: ";
    std::cin >> x;

    double result = x;

    for (int i = 0; i < numOperators; ++i) {
        if (operators[i] == "+") {
            double value;
            std::cout << "Enter value to add: ";
            std::cin >> value;
            result = add(result, value);
        } else if (operators[i] == "-") {
            double value;
            std::cout << "Enter value to subtract: ";
            std::cin >> value;
            result = subtract(result, value);
        } else if (operators[i] == "*") {
            double value;
            std::cout << "Enter value to multiply: ";
            std::cin >> value;
            result = multiply(result, value);
        } else if (operators[i] == "/") {
            double value;
            std::cout << "Enter value to divide: ";
            std::cin >> value;
            result = divide(result, value);
        } else if (operators[i] == "%") {
            int value;
            std::cout << "Enter value to mod: ";
            std::cin >> value;
            result = mod(static_cast<int>(result), value);
        } else if (operators[i] == "ln") {
            result = ln(result);
        } else if (operators[i] == "sin") {
            result = sin_func(result);
        } else if (operators[i] == "cos") {
            result = cos_func(result);
        } else if (operators[i] == "tan") {
            result = tan_func(result);
        } else if (operators[i] == "exp") {
            result = exp_func(result);
        } else {
            std::cerr << "Unknown operator: " << operators[i] << std::endl;
        }
    }

    std::cout << "Final result: " << result << std::endl;

    return 0;
}

// Function definitions
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        std::cerr << "Error: Division by zero!" << std::endl;
        return 0;
    }
}

int mod(int a, int b) {
    if (b != 0) {
        return a % b;
    } else {
        std::cerr << "Error: Modulus by zero!" << std::endl;
        return 0;
    }
}

double ln(double x) {
    if (x > 0) {
        return log(x);
    } else {
        std::cerr << "Error: ln of non-positive number!" << std::endl;
        return 0;
    }
}

double sin_func(double x) {
    return sin(x);
}

double cos_func(double x) {
    return cos(x);
}

double tan_func(double x) {
    return tan(x);
}

double exp_func(double x) {
    return exp(x);
}

//
// Created by Тимофій Безверхий on 03.07.2024.
//
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "exprtk.hpp"
using namespace std;



double Min(double values[2]){
    if (values[0] < values[1]){
        return values[0];
    } else {
        return values[1];
    }
}

double Max(double values[2]){
    if (values[0] > values[1]){
        return values[0];
    } else {
        return values[1];
    }
}

double Abs (double value){
    if (value < 0){
        return -value;
    } else {
        return value;
    }
}

double pow(double values[2]){
    int result = 1;
    for (int i = 0; i < values[2]; i++){
        result *= values[1];
    }
    return result;
}

double avg(double values[2]){
    return (values[0] + values[1]) / 2;
}

double OperatorsSort(string mainOperation, string value1, string value2 = ""){
    double values[2];
    values[0] = stod(value1);
    if (value2 != ""){
        values[1] = stod(value2);
    }
    double answer = 0;
    if (mainOperation == "min"){
        answer = Min(values);
    }
    else if (mainOperation == "max"){
        answer = Max(values);
    }
    else if (mainOperation == "abs"){
        answer = Abs(values[0]);
    }
    else if (mainOperation == "pow"){
        answer = pow(values);
    }
    else if (mainOperation == "avg"){
        answer = avg(values);
    }
    return answer;
}

bool IsSimpleNumber (string line){
    if (line[0] != '-' && !isdigit(line[0])){
        return false;
    }
    for (int i = 1; i < line.length(); i++){
        if (!isdigit(line[i])){
            return false;
        }
    }
    return true;
}

string LexorPlus(string inputString) {
    // Define the necessary types
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    string operations[] = {"min", "max", "abs", "pow", "avg"};
    string symbols[] = {"+", "-", "*", "/"};
    string mainOperation;
    string tempString;
    string tempAnswer;
    int smallExpCounter = 0;
    bool basicOperatorFound = false;
    double answer;
    for (int i = 0; i < inputString.length(); i++) {
        string probablyOperator = inputString.substr(i, 3);
        if (inputString[i] == ' '){
            continue;
        } // пробіл обробка
        else if (inputString[i] == '(') {
            smallExpCounter = 1;
            while (inputString[i+smallExpCounter] != ')') {
                tempString += inputString[i+smallExpCounter];
                smallExpCounter++;
            }
            tempAnswer = LexorPlus(tempString);
            tempString += tempAnswer;
            i += smallExpCounter;
        } // обробка дужок
        else if (probablyOperator == "min"
        || probablyOperator == "max"
        || probablyOperator == "abs"
        || probablyOperator == "pow"
        || probablyOperator == "avg") {
            smallExpCounter = 2;
            do {
                smallExpCounter++;
            } while (inputString[i + smallExpCounter-1] != '(');
            string var1 = "";
            while (inputString[i + smallExpCounter] != ',' && inputString[i + smallExpCounter] != ')') {
                 var1 += inputString[i + smallExpCounter];
                smallExpCounter++;
            }
            if (IsSimpleNumber(var1)) {
                var1 = LexorPlus(var1);
            }
            string var2 = "";
            if (probablyOperator!= "abs"){
                do {
                    smallExpCounter++;
                } while (inputString[i + smallExpCounter-1] != ',');
                while (inputString[i + smallExpCounter] != ')') {
                    var2 += inputString[i + smallExpCounter];
                    smallExpCounter++;
                }
                if (IsSimpleNumber(var2)) {
                    var2 = LexorPlus(var2);
                }
            }
            answer = OperatorsSort(probablyOperator, var1, var2);
            tempString += to_string(answer);
            i += smallExpCounter;
        } // обробка операторів
        else if (isdigit(inputString[i])|| inputString[i] == '+' || inputString[i] == '-' || inputString[i] == '*' || inputString[i] == '/' || inputString[i] == '.') {
            tempString += inputString[i];
        } // обробка чисел і операторів
    }
    if (IsSimpleNumber(tempString)){
        return tempString;
    }
    // Create a symbol table and add constants
    symbol_table_t symbol_table;
    symbol_table.add_constants();

    // Create an expression
    expression_t expression;
    expression.register_symbol_table(symbol_table);

    // Create a parser and compile the expression
    parser_t parser;
    if (!parser.compile(tempString, expression)) {
        std::cerr << "Error: Failed to compile expression." << std::endl;
        return "1";
    }
    // Evaluate the expression
    double result = expression.value();
    return to_string(result);
}



int main(){
    string inputString;

    while (true){
        getline(cin, inputString);
        string answer = LexorPlus(inputString);
        cout << answer << endl;
    }


    return 0;

}

// min(2+3, 5)
// 2 + 3 * max(5,4)
// 2 * (3 + 5 * 2)
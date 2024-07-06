//
// Created by Тимофій Безверхий on 03.07.2024.
//
#include <iostream>
#include <string>
#include <cctype>
#include <utility>
#include "exprtk.hpp"
using namespace std;

class Function {
public:
    string value;
    vector<string> parameters;
    Function(string& value, vector<string>& parameters){
        this->value = value;
        this->parameters = parameters;
    }

    Function(const Function& other) : value(other.value), parameters(other.parameters) {}

};


unordered_map<string, double> variables;
unordered_map<string, Function> definitions;
string LexorPlus(string inputString);



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

double pow(const double values[2]){
    double result = 1;
    for (int i = 0; i < values[1]; i++){
        result *= values[0];
    }
    return result;
}

double avg(const double values[2]){
    return (values[0] + values[1]) / 2;
}

double OperatorsSort(const string& mainOperation, const string& value1, const string& value2 = ""){
    double values[2];
    values[0] = stod(value1);
    if (!value2.empty()){
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
        if (!isdigit(line[i]) && line[i] != '.'){
            return false;
        }
    }
    return true;
}

void varInspector(const string& inputString){
    size_t eqPos = inputString.find('=');
    string varName = inputString.substr(0, eqPos);
    varName.erase(remove_if(varName.begin(), varName.end(), ::isspace), varName.end());
    string varValue = inputString.substr(eqPos+1);
    if (IsSimpleNumber(varValue)){
        variables[varName] = stod(varValue);
    }
    else {
        variables[varName] = stod(LexorPlus(varValue));
    }
}

//def myfunc(a, b) { min(a, b) + max(a, b) }
void funcInspector(const string& inputString){
    string funcName;
    vector<string> parameters;
    string value;
    int i = 0;
    while (inputString[i] != '(' && inputString[i] != ' '){
        funcName += inputString[i];
        i++;
    }
    string variable;
    int varCounter = 0;

    do{
        if (inputString[i] == ',' || inputString[i] == ' ' && !variable.empty()) {
            parameters.push_back(variable);
            variable = "";
            varCounter++;
        } else if (inputString[i] != ' ' && inputString[i] != '(') {
            variable += inputString[i];
        }
            i++;
    } while (inputString[i] != ')');
    varCounter++;
    parameters.push_back(variable);

    while (inputString[i-1] != '{'){
        i++;
    }

    while (inputString[i] != '}'){
        if (inputString[i] == ' '){
            i++;
            continue;
        }
        value += inputString[i];
        i++;
    }
    Function newFunction(value, parameters);
    definitions.insert(make_pair(funcName, newFunction));
}

bool CheckSurroundings (char Symbol){
    string surroundings = " /.,;:!?-+*";
    return surroundings.find(Symbol) != string::npos;

}

string FunctionHandler(string& funcName, string& inputString) {
    Function function (definitions.at(funcName));
    unordered_map<string, double> localVariables;

    int bracketsCounter = 0;
    int i = 0;
    int parametersWritten = 0;
    string oneParameter;
    while (bracketsCounter != 0 && inputString[i] != ')' || parametersWritten < function.parameters.size()) {
        if (inputString[i] == '('){
            bracketsCounter++;
        }
        else if (inputString[i] == ')'){
            bracketsCounter--;
        }

        if (inputString[i] == ',' && bracketsCounter == 1 || inputString[i] == ')' && bracketsCounter == 0){
            localVariables[function.parameters[parametersWritten]] = stod(LexorPlus(oneParameter));
            oneParameter = "";
            parametersWritten++;
        }
        else if (inputString[i] != ' ' && ((inputString[i] != '(' && inputString[i] != ')') || bracketsCounter > 1)) {
            oneParameter += inputString[i];
        }


        i++;
    }
    bool needToWrite = false;
    string expression = function.value;
    string surroundings = " /.,;:!?-+*()";
    for (int k = 0; k <= expression.length(); k++){
        for (int j = 0; j < function.parameters.size(); j++){

            if (expression.substr(k, function.parameters[j].length()) == function.parameters[j]
            && (surroundings.find(expression[k + function.parameters[j].length()])!= string::npos || k + function.parameters[j].length() == expression.length())
            && (surroundings.find(expression[k - 1])!= string::npos || k == 0)){
                expression.replace(k, function.parameters[j].length(), to_string(localVariables[function.parameters[j]]));
            }
        }
    }
    return LexorPlus(expression);
}



string LexorPlus(string inputString) {
    // Define the necessary types
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    bool isFunc = false;

    string mainOperation;
    string bracketsString;
    string tempString;
    string tempAnswer;
    int bracketsCounter = 0;
    int smallExpCounter = 0;
    double answer;
    for (int i = 0; i < inputString.length(); i++) {
        smallExpCounter = 0;
        string probablyOperator = inputString.substr(i, 3);
        if (inputString[i] == ' '){
            continue;
        }// пробіл обробка
        else if (probablyOperator == "var"){
            varInspector(inputString.substr(i+4));
            isFunc = true;
            break;
        }
        else if (probablyOperator == "def"){
            funcInspector(inputString.substr(i+4));
            isFunc = true;
            break;
        }
        else if (inputString[i] == '(') {
            smallExpCounter = 1;
            bracketsCounter = 0;
            while ((inputString[i+smallExpCounter] != ')' || bracketsCounter != 0) && (i + smallExpCounter < inputString.length())) {
                if (inputString[i+smallExpCounter] == '('){
                    bracketsCounter++;
                }
                else if (inputString[i+smallExpCounter] == ')'){
                    bracketsCounter--;
                }
                bracketsString += inputString[i+smallExpCounter];
                smallExpCounter++;
            }
            tempAnswer = LexorPlus(bracketsString);
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
            bracketsCounter = 0;
            while ((inputString[i + smallExpCounter] != ',' && inputString[i + smallExpCounter] != ')' || bracketsCounter != 0) && (i + smallExpCounter < inputString.length())) {
                if (inputString[i + smallExpCounter] == '('){
                    bracketsCounter++;
                }
                else if (inputString[i + smallExpCounter] == ')'){
                    bracketsCounter--;
                }
                var1 += inputString[i + smallExpCounter];
                smallExpCounter++;
            }
            if (!IsSimpleNumber(var1)) {
                var1 = LexorPlus(var1);
            }
            string var2 = "";
            if (probablyOperator!= "abs"){
                do {
                    smallExpCounter++;
                } while (inputString[i + smallExpCounter-1] != ',');
                bracketsCounter = 0;
                while ((inputString[i + smallExpCounter] != ')' || bracketsCounter != 0 ) && i + smallExpCounter < inputString.length()){
                    if (inputString[i + smallExpCounter] == '('){
                        bracketsCounter++;
                    }
                    else if (inputString[i + smallExpCounter] == ')'){
                        bracketsCounter--;
                    }
                    var2 += inputString[i + smallExpCounter];
                    smallExpCounter++;
                }
                if (!IsSimpleNumber(var2)) {
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
        else if (isalpha(inputString[i])){
            string variable = "";
            smallExpCounter = 0;
            while(isalpha(inputString[i+smallExpCounter])
            || isdigit(inputString[i+smallExpCounter])
            || inputString[i+smallExpCounter] == '_'
            || inputString[i+smallExpCounter] == '.'
            && (i + smallExpCounter < inputString.length())){
                variable += inputString[i+smallExpCounter];
                smallExpCounter++;
            }
            if (variables.find(variable) != variables.end()){
                tempString += to_string(variables[variable]);
            }
            else if (definitions.find(variable) != definitions.end()){ // функція
                bracketsCounter = 0;
                smallExpCounter = variable.length();
                bracketsString = "";
                while ((bracketsCounter !=0 || inputString[i+smallExpCounter-1] != ')') && i+smallExpCounter < inputString.length()){
                    if (inputString[i+smallExpCounter] == '('){
                        bracketsCounter++;
                    }
                    else if (inputString[i+smallExpCounter] == ')'){
                        bracketsCounter--;
                    }
                    bracketsString += inputString[i+smallExpCounter];
                    smallExpCounter++;
                }
                tempString += FunctionHandler(variable, bracketsString);
                i += smallExpCounter;

            }
            else {
                cout << "Variable " << variable << " is not defined" << endl;
                return " ";
            }
            i += smallExpCounter;
        } // змінна

    }

    if (isFunc){
        return " ";
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
        return "Error: Failed to compile expression.";
    }
    // Evaluate the expression
    double result = expression.value();
    return to_string(result);
}

void PropperPrint(string answer){
    bool isComma = false;
    for (int i = 0; i < answer.length(); i++) {
        if (answer[i] == '.' ) {
            isComma = true;
            if (answer[i+1] == '0'){
                break;
            }
            cout << ".";
        }
        else if (answer[i] == '0' && isComma){
            break;
        }
        else {
            cout << answer[i];
        }
    }
}

int main(){
    string inputString;
    string answer;
    try {
        do {
            getline(cin, inputString);
            answer = LexorPlus(inputString);
        }
        while (answer == " ");
        PropperPrint(answer);
    }
    catch (exception& e){
        cout << "Error: " << e.what();
    }
    return 0;
}

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

enum Token_value {
	START, END, NUMBER,
	PLUS = '+', MINUS = '-',
	MUL = '*', DIV = '/',
	LP = '(', RP = ')'
};

bool isNumber(char ch);
Token_value get_token();
double expr(bool get);
double term(bool get);
double prim(bool get);

string str, dubs;
double number;
unsigned int index;
Token_value curr_tok = START;

bool isNumber(char ch) {
	switch (ch) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '.':
		return true;
	default:
		return false;
	}
}

Token_value get_token() {
	if (index == str.length()) return curr_tok = END;
	switch (str[index]) {
	case '+': case '-':
	case '*': case '/':
	case '(': case ')':
		return curr_tok = Token_value(str[index++]);
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '.':
		dubs.clear();
		dubs.push_back(str[index]);
		while (index + 1 < str.length() && isNumber(str[index + 1])) {
			index++;
			dubs.push_back(str[index]);
		}
		index++;
		stringstream(dubs) >> number;
		return curr_tok = NUMBER;
	case ' ': case '\t':
		index++;
		return curr_tok;
	default:
		cout << "ERROR" << endl;
		return curr_tok = END;
	}
}

double expr(bool get) {
	double left = term(get);
	while (true)
		switch (curr_tok) {
		case PLUS:
			left += term(true);
			break;
		case MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
}

double term(bool get) {
	double left = prim(get);
	while (true)
		switch (curr_tok) {
		case MUL:
			left *= prim(true);
			break;
		case DIV:
			if (double d = prim(true)) {
				left /= d;
				break;
			}
			else {
				cout << "ERROR";
				return 0.0;
			}
		default:
			return left;
		}
}

double prim(bool get) {
	if (get) get_token();
	double n;
	switch (curr_tok) {
	case NUMBER:
		n = number;
		get_token();
		return n;
	case MINUS:
		get_token();
		return -number;
	case LP:
		double e = expr(true);
		if (curr_tok != RP) return 0.0;
		get_token(); // eat ’)’
		return e;
	}
}

int main() {	
	while (true) {
		getline(cin, str);
		index = 0;
		curr_tok = START;
		if (!(str.compare("exit") && str.compare("quit"))) break;
		get_token();
		cout << expr(false) << endl;
	}
	return 0;
}

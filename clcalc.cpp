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
		//cout << dubs << '\t' << "dubs" << '\t';	//DEBUG
		while (index + 1 < str.length() && isNumber(str[index + 1])) {
			index++;
			dubs.push_back(str[index]);
		}
		index++;
		stringstream(dubs) >> number;
		//cout << "number: " << number << endl;	//DEBUG
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
	//cout << "EXPR" << endl;
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
	//cout << "TERM" << endl;
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
	//cout << "PRIM" << endl;
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


// TESTS

/* TEST TOKENS
curr_tok = NUMBER;
cout << curr_tok << endl;
curr_tok = END;
cout << curr_tok << endl;
curr_tok = PLUS;
cout << curr_tok << endl;
curr_tok = MINUS;
cout << curr_tok << endl;
curr_tok = MUL;
cout << curr_tok << endl;
curr_tok = DIV;
cout << curr_tok << endl;
curr_tok = LP;
cout << curr_tok << endl;
curr_tok = RP;
cout << curr_tok << endl;
*/

/*	TEST GET_TOKEN()
while (curr_tok != END)
	cout << number << '\t' << get_token() << '\t' << number << endl;
*/

/* DFA TO CHECK INPUT VALIDITY
int state = 0;	// 0 start, 1 digit, 2 ., 3 + - * /, 4 end

for (int i = 0; i < str.length(); i++) {
	if ((state == 0 || state == 1 || state == 2 || state == 3) && (str[i] >= '0' && str[i] <= '9')) {
		state = 1;
		cout << state;
		if (i == str.length() - 1) state = 4;
	}
	else if (state == 1 && str[i] == '.') {
		state = 2;
		cout << state;
	}
	else if (state == 1 && (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')) {
		state = 3;
		cout << state;
	}
	else {
		cout << "ERROR" << endl;
		break;
	}

	if (state == 4) cout << endl;
			
	int start, end;
	start = i;
	while (str[i] > '0' && str[i] < '9' || str[i] == '.') {
		i++;
		end = i;
	}
	cout << start << " " << end << endl;
	
}
*/

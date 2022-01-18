#ifndef STACK_H
#define STACK_H

#include <vector>
using std::vector;
#include <string>
using std::string;

// TODO: Your code goes here
class Stack {
private:
	vector<double> v = vector<double>(20);
	int t = -1;
public:
	const bool empty(){
		if(t==-1){
			return true;
		}
		return false;
	}
	double pop(){
		t--;
		return v[t+1];
	}
	void push(double d){
		t++;
		v[t] = d;
	}

};
const double evaluate(string s){
	double a = 0;
	double b =0;
	double d = 0;
	Stack stack;
	string number;
	std::size_t offset = 0;

	for( char c : s) {
		if((c < '0'||c > '9') && c!='.'){
			if (number != ""){
				offset = 0;
				a = std::stod(number,&offset);
				stack.push(a);
				number = "";
			}
		}
		switch(c){
		case '+':
			a = stack.pop();
			b = stack.pop();
			d = a+b;
			stack.push(d);
			break;
		case '-':
			a = stack.pop();
			b = stack.pop();
			d = b-a;
			stack.push(d);
			break;
		case '*':
			a = stack.pop();
			b = stack.pop();
			d = b*a;
			stack.push(d);;
			break;
		case  '/':
			a = stack.pop();
			b = stack.pop();
			d = b/a;
			stack.push(d);
			break;
		case  ' ':
			break;
		default:
			number += c;
		}
	}
	return stack.pop();
}


// Do not write anything below this line

#endif

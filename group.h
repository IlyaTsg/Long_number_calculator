#pragma once
#include "polinom.h"
#include "rational.h"
#include "ll.h"
#include <stack>

enum groups
{
	polinoma = 0,
	exponent = 1,
	trigonom = 2,
	logar = 3
};

class group
{
private:
	std::vector<group*> sum;
	group* helpval;
	polinom<int, double> val;//rational< polinom< rational< ll >, rational < ll > > > val;
	groups key;

public:
	group(std::vector<group*> s, group* h, polinom<int, double> v, groups k) : sum(s), helpval(h), val(v), key(k){};
	group(int digit){
		val = digit;
		key = polinoma;
	};
	group(polinom<int, double> digit){
		val = digit;
		key = polinoma;
	};
	polinom<int, double> getVal(){ return val; }
	//Возвращает приоретет операции
	friend int priority(char op);
	//Подсчёт самого значения
	friend void action(std::stack<ll>& sum, std::stack<char>& sign);
	//Возвращает, смогла ли совершить хоть какую-нибудь операцию, работает напрямую со стеками, изменяя их
	friend ll calculate(std::string function);
	friend bool isoperation(char c);
	friend bool canAction(char op1, std::stack<char> op);
};

// Igwe Chidi 0305
int priority(char op)
{
	if(op == '(') return -1;
	else if(op=='*'||op=='/') return 1;
	else if(op=='+'||op=='-') return 2;
	else return 0;
}

// Илья Цыганков 0306
bool isoperation(char c){
    return c=='+' || c=='-' || c=='*' ||  c=='/';
}

// Илья Цыганков гр. 0306
bool canAction(char op1, std::stack<char> op)
{
    if (op.size() == 0) return false;
    int p1 = priority(op1);
    int p2 = priority(op.top());

    return p1 >= 0 && p2 >= 0 && p1 >= p2;
}

// Владислав Новиков гр. 0306
void action(std::stack<ll>& sum, std::stack<char>& sign)
{
	ll digit1 = sum.top();
	sum.pop();
	ll digit2 = sum.top();
	sum.pop();
	char op = sign.top();
	sign.pop();
    switch(op)
    {
        case '+': 
			sum.push(digit1 + digit2);
            break;
        case '-': 
			sum.push(digit2 - digit1);
            break;
        case '*': 
			sum.push(digit1*digit2);
            break;
        case '/': 
			sum.push(digit2/digit1);
            break;
    }
}

// Илья Цыганков гр. 0306
ll calculate(std::string function)
{
	std::stack<ll> digit;
	std::stack<char> operation;
	int pos = 0;
    function = "(" + function + ")";
	do{
		if(function[pos] == '(') operation.push('(');
		else if(function[pos] == ')'){
			while(operation.size() && operation.top()!='(') action(digit, operation);
			operation.pop();
		}
		else if(isoperation(function[pos])){
			while(canAction(function[pos], operation)) action(digit, operation);
			operation.push(function[pos]);
		}
		else if(isdigit(function[pos])){
            std::string a = "";
            while(pos < function.length() && isdigit(function[pos])){ 
                a += function[pos];
                pos++;
            }
            pos--;
            digit.push(ll(a));
        }
		else{
			while(!isdigit(function[pos]) && !isoperation(function[pos]) && function[pos]!='(' && function[pos] != ')') pos++;
			pos--;
		}
		pos++;
	}while(pos<function.length());
	if(digit.size()>1 || operation.size()>0); // Отлов ошибки(типо ввёл неправильно и т.д)
	return digit.top();
}
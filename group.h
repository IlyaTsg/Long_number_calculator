#pragma once
#include "polinom.h"
#include "rational.h"
#include "ll.h"
#include <stack>

enum groups
{
	polinom,
	exponent,
	trigonom,
	logar,
};

class group
{
private:
	vector<group*> sum;
	group* helpval;
	polinom<int, double> val;//rational< polinom< rational< ll >, rational < ll > > > val;
	groups key;

public:
	group() {}

	//Переводит группу в новое состояние
	friend void transit(group& num);
	//Возвращает, смогла ли совершить хоть какую-нибудь операцию, работает напрямую со стеками, изменяя их
	friend bool computer(std::stack<group>& sum, std::stack<std::string>& sign);
	//Получает строку и два стека, которые заполнит
	friend void stroker(std::string val, std::stack<group>& sum, std::stack<std::string>& sign);
};

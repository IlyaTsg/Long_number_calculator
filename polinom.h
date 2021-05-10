#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include "ll.h"
#include "rational.h"


//класс полиномов
//словарь коэффициентов (COEF) и вектор степеней (IND), они отсортированы по возрастанию
//мы передаем ключ - степень x, перед которым стоит ненулевой коэффициент, и получаем сам коэффициент
template <class IND, class COEF>
class polinom
{
private:
	std::vector<IND> ind;
	std::map<IND, COEF> coef;

public:
	polinom<IND, COEF>() {}
	template <class type> polinom<IND, COEF>(type N)
	{
		COEF n = COEF(N);
		if (n >= 0.0001 || n <= -0.0001)
		{
			ind.push_back(0);
			coef[0] = n;
		}
	}
	template <class type1, class type2> polinom<IND, COEF>(type1 L, type2 N) 
	{ 
		IND l = IND(L);
		COEF n = COEF(N);
		if (n >= 0.0001 || n <= -0.0001)
		{
			ind.push_back(l);
			coef[l] = n;
		}
	}
	polinom<IND, COEF>(std::vector<COEF> Coef)
	{
		for (int i = 0, n = Coef.size(); i < n; i++)
		{
			if (Coef[i] >= 0.001 || Coef[i] <= -0.001)
			{
				ind.push_back(IND(i));
				coef[IND(i)] = Coef[i];
			}
		}
	}
	polinom<IND, COEF>(std::vector<IND> Ind, std::map<IND, COEF> Coef) : ind(Ind), coef(Coef) {}
	polinom<IND, COEF>(std::vector<IND> Ind, std::vector<COEF> Coef) : ind(Ind) { for (int i = 0, n = Ind.size(); i < n; i++) coef[ind[i]] = Coef[i]; }
	polinom<IND, COEF>(std::string pol)
	{
		std::string polres = "";
		pol = "#" + pol;
		bool k = 0, upkey = 0;
		for (int i = 0; pol[i]; i++, k = 0)
		{
			while (pol[i] && (pol[i] == ' ' || pol[i] == '*' || pol[i] == ')' || pol[i] == '(')) pol.erase(i, 1);
			if (pol[i] == 'x')
			{
				if (pol[i - 1] < '0' || pol[i - 1] > '9') polres = polres + '1';
				if (pol[i + 1] != '^') k = 1;
			}
			polres = polres + pol[i];
			if (k) polres = polres + "^1";
		}
		for (int i = 0, n = polres.size(); i < n; i++)
		{
			if (polres[i] >= '0' && polres[i] <= '9' && polres[i - 1] != '^' && polres[i - 1] != '/' && polres[i - 1] != '.' && (polres[i - 1] < '0' || polres[i - 1] > '9'))
			{
				while (i < n && (polres[i] >= '0' && polres[i] <= '9' || polres[i] == '.' || polres[i] == '/')) i++;
				if (i == n || polres[i] != 'x')
				{
					polres.insert(i, "x^0");
					n = polres.size();
				}
			}
		}
		polres = polres + '+';
		polres.erase(0, 1);
		std::cout << polres << '\n';
		std::string num;
		COEF Coef;
		IND Ind;
		for (int i = 0, n = polres.size(); i < n; i++)
		{
			if (polres[i] == 'x')
			{
				std::istringstream in(num);
				in >> Coef;
				num = "";
				i += 2;
			}
			else if (i && (polres[i] == '-' || polres[i] == '+'))
			{
				std::istringstream in(num);
				in >> Ind;
				if (Coef < -0.0001 || 0.0001 < Coef)
				{
					ind.push_back(IND(Ind));
					coef[Ind] = COEF(Coef);
				}
				num = "";
				if (polres[i] == '+') i++;
			}
			if (i < n) num = num + polres[i];
		}
		std::sort(ind.begin(), ind.end());
	}

	template <class IND, class COEF> friend bool operator ==(const polinom<IND, COEF>&, const polinom<IND, COEF>&);
	//template <class IND, class COEF, class type> friend bool operator ==(const polinom<IND, COEF>& l_val, const type& r_val) { return (l_val == polinom<IND, COEF>(r_val)); }
	//template <class IND, class COEF, class type> friend bool operator ==(const type& l_val, const polinom<IND, COEF>& r_val) { return (r_val == l_val); }

	friend bool operator !=(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val) { return (!(l_val == r_val)); }
	//template <class IND, class COEF, class type> friend bool operator !=(const polinom<IND, COEF>& l_val, const type& r_val) { return (l_val != polinom<IND, COEF>(r_val)); }
	//template <class IND, class COEF, class type> friend bool operator !=(const type& l_val, const polinom<IND, COEF>& r_val) { return (r_val != l_val); }

	template <class INDa, typename COEFa> friend polinom<INDa, COEFa> operator -(polinom<INDa, COEFa>&);
	template <class INDa, class COEFa> friend polinom<INDa, COEFa> operator +(polinom<INDa, COEFa>&, polinom<INDa, COEFa>&);
	template <class INDa, class COEFa> friend polinom<INDa, COEFa> operator -(polinom<INDa, COEFa>&, polinom<INDa, COEFa>&);
	template <class INDa, class COEFa> friend polinom<INDa, COEFa> operator *(polinom<INDa, COEFa>&, polinom<INDa, COEFa>&);
	template <class INDa, class COEFa> friend polinom<INDa, COEFa> operator /(polinom<INDa, COEFa>&, polinom<INDa, COEFa>&);
	template <class INDa, class COEFa> friend polinom<INDa, COEFa> operator %(polinom<INDa, COEFa>&, polinom<INDa, COEFa>&);
	/*std::ostream& operator>> (std::ostream& out, const polinom& val);
	vector< complex<T> > roots();
	friend polinom gcd(polinom l_val, polinom r_val);*/
	template <class INDa, class COEFa> friend COEFa substitution(polinom<INDa, COEF>& val, COEFa& x);
	template <class INDa, class COEFa> friend COEFa integral(polinom<INDa, COEFa>& pol, COEFa& l_val, COEFa& r_val);
	template <class INDa, class COEFa> friend polinom<INDa, COEFa> derivative(polinom<INDa, COEFa>& val);
	template <class INDa, class COEFa> friend polinom<INDa, COEFa> integral(polinom<INDa, COEFa>& val, COEFa& C);
	template <class INDa, class COEFa> friend std::ostream& operator<< (std::ostream&, polinom<INDa, COEFa>&);
};


// оператор равенства (равны ли два полинома)
// Если количество ненулевыфх коэффициентов не равно количеству второго, то возвращаем false
// Иначе в цикле сравниваем коэффициенты по степеням и сами степени
// В случае неравенства - false, если ни разу не было false, то возвращаем true
template <class IND, class COEF>
bool operator ==(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
	polinom<IND, COEF> lv = l_val,
		rv = r_val;
	int n = l_val.ind.size();
	if (n != r_val.ind.size()) return false;
	for (int i = 0; i < n; i++)
	{
		if (l_val.ind[i] != r_val.ind[i]) return false;
		if (lv.coef[l_val.ind[i]] != rv.coef[r_val.ind[i]]) return false;
	}
	return true;
}

/*Вычисление определенного интеграла
  В функцию передается сам полином, и границы интеграла: нижняя и верхняя соответственно
  Вызывается функция, вычисляющая неопределенный интеграл (ее результат записывается в новый полином)
  Результат считается по формуле Ньютона-Лейбница (с помощью функции вычисления значения интеграла substitution)
*/
template <class IND, class COEF>
COEF integral(polinom<IND, COEF>& pol, COEF& l_val, COEF& r_val)
{
	polinom<IND, COEF> F = integral(pol, l_val);
	return (substitution(F, r_val) - substitution(F, l_val));
}


/*Бинарное возведение в степень
 Заметим, что x^(2n) = (x^2^(n - 1))^2
 Если вместо а и b подставлять степени двойки, то получится, что мы можем произвольно складывать степени двойки в показателе числа
 представим искомый показатель в двоичном виде и найдем соответствующие степени двойки в показателе
 */
template <typename IND, typename COEF>
COEF power1(COEF key, IND ind)
{
	std::vector<COEF> power2;
	power2.push_back(key);
	for (COEF i = 2; i < ind; i = i * i) power2.push_back(power2[power2.size() - 1] * power2[power2.size() - 1]);
	power2.push_back(power2[power2.size() - 1] * power2[power2.size() - 1]);

	//for (int i = 0; i < power2.size(); i++) std::cout << power2[i] << ' ';
	//std::cout << std::endl;

	int sum = 0;
	COEF ans = 1;
	for (int i = 1, n = power2.size(); i <= n && sum < ind; i++)
	{
		if (sum + (1 << (n - i)) <= ind)
		{
			sum += (1 << (n - i));
			ans = ans * power2[n - i];
		}
	}
	return ans;
}

// подстановка значений в полином
// передается полином и значение х, которое нужно подставить в полином
// в цикле вычисляем значение полинома 
// выводим число, которое является значением полинома при таком х
template <typename IND, typename COEF>
COEF substitution(polinom<IND, COEF>& val, COEF& x)
{
	COEF sum = 0;
	for (const IND& to : val.ind) sum = sum + val.coef[to] * power1(x, to);
	return sum;
}

// Слияние двух отсортированных векторов, возвращающее отсортированный вектор за линейное время
// Объединение двух множеств
template <typename IND>
std::vector<IND> merge(const std::vector<IND>& l_val, const std::vector<IND>& r_val)
{
	int a = l_val.size(), b = r_val.size();
	std::vector<IND> ans;
	for (int l = 0, r = 0; l < a || r < b;)
	{
		if (r == b || l < a && l_val[l] <= r_val[r])
		{
			if (r < b && l_val[l] == r_val[r]) r++;
			ans.push_back(l_val[l++]);
		}
		else ans.push_back(r_val[r++]);
	}
	return ans;
}

// унарный минус
// в цикле изменяет знаки перед коэффициентами полинома
//возвращает вектор степеней и массив новых коэффициентов
template <class IND, class COEF>
polinom<IND, COEF> operator -(const polinom<IND, COEF>& val)
{
	polinom<IND, COEF> value = val;
	std::map<IND, COEF> new_coef;
	for (const COEF& to : val.ind) new_coef[to] = -value.coef[to];
	return polinom<IND, COEF>(val.ind, new_coef);
}

// вычитание полиномов
// Объединяем множества показателей
// вычитаем соответствующие коэффициенты
// Удаляем образовавшиеся нули
//возвращаем новые вектор степеней и словарь коэф.
template <typename IND, typename COEF>
polinom<IND, COEF> operator -(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
	polinom<IND, COEF> lv = l_val,
		rv = r_val;
	std::vector<IND> new_ind = merge(lv.ind, rv.ind);
	std::map<IND, COEF> new_coef;
	for (const IND& to : new_ind) new_coef[to] = lv.coef[to] - rv.coef[to];
	int l = 0;
	for (const IND& to : new_ind) if (new_coef[to] != 0) new_ind[l++] = to;
	new_ind.resize(l);
	return polinom<IND, COEF>(new_ind, new_coef);
}


// сложение полиномов
// объединяем множества показателей
//Складываем соответствующие коэффициенты 
//удаляем образующиеся нули
//возвращаем новые вектор степеней и словарь коэф.
template <typename IND, typename COEF>
polinom<IND, COEF> operator +(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
	polinom<IND, COEF> lv = l_val,
		rv = r_val;
	std::vector<IND> new_ind = merge(lv.ind, rv.ind);
	std::map<IND, COEF> new_coef;
	for (const IND& to : new_ind) new_coef[to] = lv.coef[to] + rv.coef[to];
	int l = 0;
	for (const IND& to : new_ind) if (new_coef[to] != 0) new_ind[l++] = to;
	new_ind.resize(l);
	return polinom<IND, COEF>(new_ind, new_coef);
}
// оператор вывода
template <typename IND, typename COEF>
std::ostream& operator<< (std::ostream& out, const polinom<IND, COEF>& val)
{
	polinom<IND, COEF> value = val;
	int n = value.ind.size();
	if (n == 0) out << 0;
	else for (int i = 0; i < n; i++)
	{
		IND to = value.ind[n - i - 1];
		if (i && value.coef[to] > 0) out << "+";
		if (value.coef[to] == -1) out << '-';
		else if (to == 0 || !(value.coef[to] <= 1.0001 && value.coef[to] >= 0.9999)) out << value.coef[to];
		if (to > 0) out << 'x';
		if (to > 1)
		{
			out << "^" << to;
			if (i < n - 1) out << ' ';
		}
	}
	return out;
}

// оператор ввода
// вводится строка из которой удаляются все пробелы, (), *, х
// потом он добавляет числа перед х
//добавляет х к свободному коэффициенту
//добавляет степень ко всем x
// считывает числло до х и степень до знака + , -
// Если коэффициент ненулевой то он добавляет его 

template<class IND, class COEF>
std::istream& operator>> (std::istream& in, polinom<IND, COEF>& val)
{
	std::string value;
	getline(in, value);
	val = polinom<IND, COEF>(value);
	return in;
}
// умножение полиномов
template <typename IND, typename COEF>
polinom<IND, COEF> operator *(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
	polinom<IND, COEF> lv = l_val,
		rv = r_val;
	if (l_val == polinom<IND, COEF>(0) || r_val == polinom<IND, COEF>(0)) return polinom<IND, COEF>();
	IND comp = std::max(l_val.ind[l_val.ind.size() - 1], r_val.ind[r_val.ind.size() - 1]);
	/* умножение полиномов степени большей чем 1000000. Стандартное умножение "в столбик"
	   создается новый вектор степеней и новый словарь коэффициентов
	   смотрим на все степени и попарно перемножаем их
	   сортируем вектор степеней
	   возвращаем отсортированный вектор степение и новый словарь коэффициентов*/
	if (1)
	{
		std::vector<IND> new_ind;
		std::map<IND, COEF> new_coef;
		for (const IND& l : l_val.ind)
		{
			for (const IND& r : r_val.ind)
			{
				//std::cout << l << ' ' << r << '\n';
				new_coef[l + r] = new_coef[l + r] + lv.coef[l] * rv.coef[r];
				new_ind.push_back(l + r);
			}
		}
		std::sort(new_ind.begin(), new_ind.end());
		int l = 1, n = new_ind.size();
		for (int i = 1; i < n; i++) if (new_ind[i] != new_ind[i - 1] && new_coef[new_ind[i]] != 0) new_ind[l++] = new_ind[i];
		new_ind.resize(l);
		return polinom<IND, COEF>(new_ind, new_coef);
	}
	/*else
	{
		/*
		умножение полиномов степени выше 1000000
		1) Находим минимальные и максимальные элементы у полиномов;
		2) Изменяем размер векторов
		3) заполняем векторы коэффициентов со смещением на минимальную степень.
		4) выделяем 2^(n+1) мест под значения полиномов
		5) применяем алгоритм БПФ
		6) в res записываем вещественную часть от коэффициентов
		7) Возвращаем вектор новых коэффициентов и степеней
		*
		int value = 0;
		auto minorl = std::min_element(l_val.ind.begin(), l_val.ind.end());
		auto minorr = std::min_element(r_val.ind.begin(), r_val.ind.end());
		auto maxl = std::max_element(l_val.ind.begin(), l_val.ind.end());
		auto maxr = std::max_element(r_val.ind.begin(), r_val.ind.end());
		std::vector < std::complex<long double>> fr, fl, result;
		fr.resize((*maxr - (*minorr) + 1), value);
		fl.resize((*maxl - (*minorl) + 1), value);
		for (const auto& l : l_val.ind) fl[l - *minorl] = l_val.coef[l];
		for (const auto& r : r_val.ind) fr[r - *minorr] = r_val.coef[r];
		size_t n = 1;
		while (n < std::max(fr.size(), fl.size())) n <<= 1;
		n <<= 1;
		fr.resize(n, value); fl.resize(n);
		fft(fr, false);
		fft(fl, false);
		for (size_t i = 0; i < n; i++) fr[i] *= fl[i];
		fft(fr, true);
		result.resize(n);
		std::vector<long double> res;
		res.resize(n);
		for (size_t i = 0; i < n; i++) res[i] = double(fr[i].real());
		std::vector<IND> newind;
		std::map<IND, COEF> newcoef;
		int vinos = *minorl + (*minorr);
		for (size_t i = 0; i <= *maxl + *maxr; i++)
		{
			if (i < res.size() && res[i] != 0)
			{
				newind.push_back(i + vinos);
				newcoef[i + vinos] = res[i];
			}
		}
		return polinom<IND, COEF>(newind, newcoef);
	}*/
}
// деление полиномов
// стандартное деление "в столбик"
// если делимое меньше делителя, то возвращается 0
// пока степень делителя меньше степени делимого то выполняем стандартное деление в столбик
// возвращаем новый вектор степеней и новый словарь коэф.
template <typename IND, typename COEF>
polinom<IND, COEF> operator /(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
	//std::cout << "\n\n\n";
	assert(r_val != (polinom<IND, COEF>(0)));
	polinom<IND, COEF> rv = r_val;
	std::vector<IND> new_ind;
	std::map<IND, COEF> new_coef;
	if (r_val.ind[r_val.ind.size() - 1] > l_val.ind[l_val.ind.size() - 1]) return polinom<IND, COEF>(new_ind, new_coef);
	polinom<IND, COEF> div(l_val);
	IND r = r_val.ind[r_val.ind.size() - 1], l = div.ind[div.ind.size() - 1];
	while (r <= l)
	{
		//std::cout << l << ' ' << r << ' ' << (l - r) << std::endl;
		new_ind.push_back(l - r);
		new_coef[l - r] = div.coef[l] / rv.coef[r];
		//std::cout << new_coef[l - r] << std::endl;
		polinom<IND, COEF> g(l - r, new_coef[l - r]);
		//std::cout << g << std::endl;
		g = g * rv;
		//std::cout << g << std::endl;
		div = div - g;
		//std::cout << l << std::endl;
		l = (div.ind.size() != 0 ? div.ind[div.ind.size() - 1] : -1);
	}
	for (int i = 0, n = new_ind.size(); i < n / 2; i++) std::swap(new_ind[i], new_ind[n - i - 1]);
	return polinom<IND, COEF>(new_ind, new_coef);
}
// производная
// в функцию передается полином
// создается новый вектор степеней и новый словарь коэффициентов
// в цикле опускаем степень каждого одночлена на 1 и домножаем коэффициет на эту степень
// возвращаем новый вектор степеней и новый словарь коэффициентов
template <typename IND, typename COEF>
polinom<IND, COEF> derivative(polinom<IND, COEF>& val)
{
	std::vector<IND> new_ind;
	std::map<IND, COEF> new_coef;
	for (int i = (val.ind[0] == 0), n = val.ind.size(); i < n; i++)
	{
		new_ind.push_back(val.ind[i] - 1);
		new_coef[val.ind[i] - 1] = val.coef[val.ind[i]] * val.ind[i];
	}
	return polinom<IND, COEF>(new_ind, new_coef);
}

// неопределенный интеграл
// в функцию передается константа интеграла и сам полином
// если константа ненулевая, то в новый вектор степеней мы добавляем нулевую степень, а в словарь коэффициентов записываем константу при нулевой степени х (свободный член)
// в цикле увеличиваем степень одночленов на 1, коэффициенты вычисляем по формуле val.coef[val.ind[i]] / (val.ind[i] + 1)
// возвращаем новый вектор степеней и новый словарь коэффициентов
template <typename IND, typename COEF>
polinom<IND, COEF> integral(polinom<IND, COEF>& val, COEF& C)
{
	std::vector<IND> new_ind;
	std::map<IND, COEF> new_coef;
	if (C != 0)
	{
		new_ind.push_back(0);
		new_coef[0] = C;
	}
	for (int i = 0, n = val.ind.size(); i < n; i++)
	{
		new_ind.push_back(val.ind[i] + 1);
		new_coef[val.ind[i] + 1] = val.coef[val.ind[i]] / (val.ind[i] + 1);
	}
	return polinom<IND, COEF>(new_ind, new_coef);
}
// остаток от деления
// в функцию передаются делимое и делитель (полиномы)
// создаем полином help в который записываем целую часть от деления данных многочленов и полином для ответа, в который изначально записывается делимое
// Далее целую часть от деления мы умножаем на делитель и вычитаем из делимого
// возвращаем вектор, в котором остается остаток от деления
template <typename IND, typename COEF>
polinom<IND, COEF> operator %(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
	polinom<IND, COEF> ans = l_val, help = l_val / r_val;
	help = help * r_val;
	ans = l_val - help;
	return ans;
}

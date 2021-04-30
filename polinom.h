#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

template <typename COEF>
long long intstr(std::string str, int i = 0)
{
	long long n = str.size(), sum = 0;
	for (; i < n && str[i] >= '0' && str[i] <= '9'; i++) sum = 10LL * sum + static_cast<long long>(str[i] - '0');
	return sum;
}

template <class IND, class COEF>
class polinom
{
private:
	std::vector<IND> ind;
	std::map<IND, COEF> coef;

public:
	polinom<IND, COEF>() {}
	polinom<IND, COEF>(COEF n) : ind({ 0 }) { coef[0] = n; }
	polinom<IND, COEF>(IND l, COEF n) : ind({ l }) { coef[l] = n; }
	polinom<IND, COEF>(std::vector<IND> Ind, std::map<IND, COEF> Coef) : ind(Ind), coef(Coef) {}
	polinom<IND, COEF>(std::vector<IND> Ind, std::vector<COEF> Coef) : ind(Ind) { for (int i = 0, n = Ind.size(); i < n; i++) coef[ind[i]] = Coef[i]; }
	//polinom<IND, COEF>(std::string pol)

	template <class IND, class COEF> friend polinom<IND, COEF> operator -(polinom<IND, COEF>&);
	template <class IND, class COEF> friend polinom<IND, COEF> operator +(polinom<IND, COEF>&, polinom<IND, COEF>&);
	template <class IND, class COEF> friend polinom<IND, COEF> operator -(polinom<IND, COEF>&, polinom<IND, COEF>&);
	template <class IND, class COEF> friend polinom<IND, COEF> operator *(polinom<IND, COEF>&, polinom<IND, COEF>&);
	template <class IND, class COEF> friend polinom<IND, COEF> operator /(polinom<IND, COEF>&, polinom<IND, COEF>&);
	template <class IND, class COEF> friend polinom<IND, COEF> operator %(polinom<IND, COEF>&, polinom<IND, COEF>&);
	/*std::ostream& operator>> (std::ostream& out, const polinom& val);
	vector< complex<T> > roots();
	friend polinom gcd(polinom l_val, polinom r_val);*/
	template <class IND, class COEF> friend COEF substitution(polinom<IND, COEF>& val, COEF& x);
	template <class IND, class COEF> friend COEF integral(polinom<IND, COEF>& pol, COEF& l_val, COEF& r_val);
	template <class IND, class COEF> friend polinom<IND, COEF> derivative(polinom<IND, COEF>& val);
	template <class IND, class COEF> friend polinom<IND, COEF> integral(polinom<IND, COEF>& val, COEF& C);
	template <class IND, class COEF> friend std::ostream& operator<< (std::ostream&, polinom<IND, COEF>&);
};
/*Вычисление интеграла*/
template <class IND, class COEF> 
COEF integral(polinom<IND, COEF>& pol, COEF& l_val, COEF& r_val)
{
	polinom<IND, COEF> F = integral(pol, l_val);
	return (substitution(F, r_val) - substitution(F, l_val));
}
/*Бинарное возведение в степень*/
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
template <typename IND, typename COEF>
COEF substitution(polinom<IND, COEF>& val, COEF& x)
{
	COEF sum = 0;
	for (const IND& to : val.ind) sum = sum + val.coef[to] * power1(x, to);
	return sum;
}
// Слияние двух отсортированных векторов, возвращающее отсортированный вектор за линейное время
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
template <class IND, class COEF> 
polinom<IND, COEF> operator -(polinom<IND, COEF>& val)
{
	std::map<IND, COEF> new_coef;
	for (const auto& to : val.ind) new_coef[to] = -val.coef[to];
	return polinom<IND, COEF>(val.ind, new_coef);
}
// вычитание полиномов
template <typename IND, typename COEF>
polinom<IND, COEF> operator -(polinom<IND, COEF>& l_val, polinom<IND, COEF>& r_val)
{
	std::vector<IND> new_ind = merge(l_val.ind, r_val.ind);
	std::map<IND, COEF> new_coef;
	for (const auto& to : new_ind) new_coef[to] = l_val.coef[to] - r_val.coef[to];
	int l = 0;
	for (const auto& to : new_ind) if (new_coef[to] != 0) new_ind[l++] = to;
	new_ind.resize(l);
	return polinom<IND, COEF>(new_ind, new_coef);
}
// сложение многочленов
template <typename IND, typename COEF>
polinom<IND, COEF> operator +(polinom<IND, COEF>& l_val, polinom<IND, COEF>& r_val)
{
	std::vector<IND> new_ind = merge(l_val.ind, r_val.ind);
	std::map<IND, COEF> new_coef;
	for (const auto& to : new_ind) new_coef[to] = l_val.coef[to] + r_val.coef[to];
	int l = 0;
	for (const auto& to : new_ind) if (new_coef[to] != 0) new_ind[l++] = to;
	new_ind.resize(l);
	return polinom<IND, COEF>(new_ind, new_coef);
}
// оператор вывода
template <typename IND, typename COEF>
std::ostream& operator<< (std::ostream& out, polinom<IND, COEF>& val)
{
	int n = val.ind.size();
	if (n == 0) out << 0;
	else for (int i = 0; i < n; i++)
	{
		IND to = val.ind[n - i - 1];
		if (i && val.coef[to] > 0) out << "+";
		if (val.coef[to] == -1) out << '-';
		else if (to == 0 || !(val.coef[to] <= 1.0001 && val.coef[to] >= 0.9999)) out << val.coef[to];
		if (to > 0) out << 'x';
		if (to > 1)
		{
			out << "^" << to;
			if (i < n - 1) out << ' ';
		}
	}
	return out;
}
// умножение полиномов
template <typename IND, typename COEF> 
polinom<IND, COEF> operator *(polinom<IND, COEF>& l_val, polinom<IND, COEF>& r_val)
{
	COEF comp = std::max(l_val.ind[l_val.ind.size() - 1], r_val.ind[r_val.ind.size() - 1]);
	/* умножение полиномов степени большей чем 1000000. Стандартное умножение "в столбик"*/
	if (comp * sizeof(COEF) > static_cast<long long>(1 << 30))
	{
		std::vector<IND> new_ind;
		std::map<IND, COEF> new_coef;
		for (const auto& l : l_val.ind)
		{
			for (const auto& r : r_val.ind)
			{
				new_coef[l + r] = new_coef[l + r] + l_val.coef[l] * r_val.coef[r];
				new_ind.push_back(l + r);
			}
		}
		std::sort(new_ind.begin(), new_ind.end());
		int l = 1, n = new_ind.size();
		for (int i = 1; i < n; i++) if (new_ind[i] != new_ind[i - 1] && new_coef[new_ind[i]] != 0) new_ind[l++] = new_ind[i];
		new_ind.resize(l);
		return polinom<IND, COEF>(new_ind, new_coef);
	}
	else 
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
		*/
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
	}
}
// деление полиномов
//реализовано через умножение
template <typename IND, typename COEF>
polinom<IND, COEF> operator /(polinom<IND, COEF>& l_val, polinom<IND, COEF>& r_val)
{
	std::vector<IND> new_ind;
	std::map<IND, COEF> new_coef;
	if (r_val.ind[r_val.ind.size() - 1] > l_val.ind[l_val.ind.size() - 1]) return polinom<IND, COEF>(new_ind, new_coef);
	polinom<IND, COEF> div(l_val);
	int r = r_val.ind[r_val.ind.size() - 1], l = div.ind[div.ind.size() - 1];
	while (r <= l)
	{
		new_ind.push_back(l - r);
		new_coef[l - r] = div.coef[l] / r_val.coef[r];
		polinom<IND, COEF> g(l - r, new_coef[l - r]);
		g = g * r_val;
		div = div - g;
		l = (div.ind.size() != 0 ? div.ind[div.ind.size() - 1] : -1);
	}
	for (int i = 0, n = new_ind.size(); i < n / 2; i++) std::swap(new_ind[i], new_ind[n - i - 1]);
	return polinom<IND, COEF>(new_ind, new_coef);
}
// производная
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

// интеграл
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
template <typename IND, typename COEF> 
polinom<IND, COEF> operator %(polinom<IND, COEF>& l_val, polinom<IND, COEF>& r_val)
{
	polinom<IND, COEF> ans = l_val, help = l_val / r_val;
	help = help * r_val;
	ans = l_val - help;
	return ans;
}

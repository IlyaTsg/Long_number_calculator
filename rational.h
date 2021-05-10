#pragma once
#include "ll.h"

/** \class rational
 *  \brief Класс очень длинных натуральных чисел
 *	\details Реализует в себе все необходимо-достаточные возможности для работы с очень длинным рациональными числами, такие как сравнение, и простейщие арифметические операции, а так же вывод их в стандартные потоки\n
 * 	Само рациональное число представлено в виде дроби: числитель/знаменатель
 *  \authors Тимур и Мария
 */

 //Турушев Тимур 0306
template <class T>
class rational
{
private:
	T num = 0;
	T den = 1;

public:
	rational<T>() {};
	rational<T>(T num, T den) : num(num), den(den) { assert(den != 0); red(*this); }
	rational<T>(T num) : num(num), den(T(1)) {}
	rational(std::string rat);
	rational<T>(long double value);
	rational<T> operator -() { return rational<T>(-num, den); }
	T getNum() { return num; }
	T getDen() { return den; }
	friend bool isnum(rational<T> val) { return (val.den == 1); }

	/** \brief Сравнение 2 чисел
	 * \details Сравнение рациональных чисел
	 * \param secval const rational<T>& lv, const rational<T>& rv
	 * \return bool true - если верно, false - если неверно
	 * \authors Шкода Мария 0306
	 */

	friend bool operator ==(const rational<T>& lv, const rational<T>& rv) { return (lv.num == rv.num && lv.den == rv.den); }
	template <class type> friend bool operator ==(const rational<T>& lv, const type& rv) { return (lv == rational<T>(rv)); }
	template <class type> friend bool operator ==(const type& lv, const rational<T>& rv) { return (rational<T>(lv) == rv); }
	friend bool operator < (const rational<T>& lval, const rational<T>& rval) {
		rational<T> rv = rval;
		rational<T> lv = lval;
		if (lv.den == rv.den) return (lv.num < rv.num);
		else {
			comden(lv, rv);
			return (lv.num < rv.num);
		}
	}
	template <class type> friend bool operator < (const rational<T>& lv, const type& rv) { return (lv < rational<T>(rv)); }
	template <class type> friend bool operator < (const type& lv, const rational<T>& rv) { return (rational<T>(lv) < rv); }

	friend bool operator !=(const rational<T>& lval, const rational<T>& rval) { return (!(lval == rval)); }
	template <class type> friend bool operator !=(const rational<T>& lv, const type& rv) { return (lv != rational<T>(rv)); }
	template <class type> friend bool operator !=(const type& lv, const rational<T>& rv) { return (rational<T>(lv) != rv); }

	friend bool operator > (const rational<T>& lval, const rational<T>& rval) { return (lval != rval && !(lval < rval)); }
	template <class type> friend bool operator > (const rational<T>& lv, const type& rv) { return (lv > rational<T>(rv)); }
	template <class type> friend bool operator > (const type& lv, const rational<T>& rv) { return (rational<T>(lv) > rv); }

	friend bool operator >=(const rational<T>& lval, const rational<T>& rval) { return (!(lval < rval)); }
	template <class type> friend bool operator >=(const rational<T>& lv, const type& rv) { return (lv >= rational<T>(rv)); }
	template <class type> friend bool operator >=(const type& lv, const rational<T>& rv) { return (rational<T>(lv) >= rv); }

	friend bool operator <=(const rational<T>& lval, const rational<T>& rval) { return (!(lval > rval)); }
	template <class type> friend bool operator <=(const rational<T>& lv, const type& rv) { return (lv <= rational<T>(rv)); }
	template <class type> friend bool operator <=(const type& lv, const rational<T>& rv) { return (rational<T>(lv) <= rv); }
	friend rational<T> operator +(const rational<T>& lval, const rational<T>& rval) {
		rational<T> res;
		rational<T> rv = rval;
		rational<T> lv = lval;
		comden(rv, lv);
		res.num = rv.num + lv.num;
		res.den = rv.den;
		red(res);
		return res;
	}
	//template <class T> friend rational<T> operator %(const rational<T>& lval, const rational<T>& rval);
	friend rational<T> operator *(const rational<T>& lval, const rational<T>& rval) {
		rational<T> res;
		res.num = rval.num * lval.num;
		res.den = lval.den * rval.den;
		red(res);
		return res;
	}
	friend rational<T> operator /(const rational<T>& lval, const rational<T>& rval) {
		rational<T> res;
		res.num = rval.den * lval.num;
		res.den = rval.num * lval.den;
		assert(res.den != 0);
		red(res);
		return res;
	}
	//Турушев Тимур 0306

	friend std::ostream& operator<< (std::ostream& out, const rational<T>& val) {
		out << val.num;
		if (val.den != 1) out << "/" << val.den;
		return out;
	}

	friend std::istream& operator>> (std::istream& in, rational<T>& val) {
		std::string line;
		in >> line;
		val = rational<T>(line);
		return in;
	}
	/*friend std::ostream& operator<< (std::ostream& out, rational<polinom<> >& val) {
		out << val.num << "/" << val.den;
		return out;
	}*/
	//friend std::ostream& operator<< (std::ostream& out, const rational<ll>& val);
	/** \brief Сокращение дроби
	 * \details Деление числителя и знаменателя на их нод
	 * \param secval rational<T>& to
	 * \authors Турушев Тимур 0306
	 */
	 //Reduction
	friend void red(rational<T>& to) {
		T frac_gcd = gcd(to.num, to.den);
		to.num = to.num / frac_gcd;
		to.den = to.den / frac_gcd;
		if (to.den < 0) {
			to.den = -to.den;
			to.num = -to.num;
		}
	}
	//Мария Шкода 0306
	/** \brief Приведение к общему знамантелю
	 * \details Операция реализована с помощью нок
	 * \param secval rational<T>& lval, rational<T>& rval
	 * \authors Шкода Мария 0306
	 */
	 //Reduction to a common denominator
	void static comden(rational<T>& lval, rational<T>& rval) {
		T cden = lcm(lval.den, rval.den);
		assert(cden != 0);
		lval.num = lval.num * (cden / lval.den);
		rval.num = rval.num * (cden / rval.den);
		lval.den = cden;
		rval.den = cden;
	}
	/** \brief Вычитание
	 * \details Используется приведение к общему знаменателю. После этой операции числитель правой операнды вычитается из левой
	 * \param secval const rational<T>& lval, const rational<T>& rval
	 * \return vln разность
	 * \authors Шкода Мария 0306
	 */
	friend rational<T> operator -(const rational<T>& lval, const rational<T>& rval) {
		rational<T> res;
		rational<T> rv = rval;
		rational<T> lv = lval;
		comden(rv, lv);
		res.num = lv.num - rv.num;
		res.den = rv.den;
		red(res);
		return res;
	}
};
//Турушев Тимур 0306

/** \brief Специализации конструкторов
 * \details Формат строки - "(sign)num/den"
 * \authors Турушев Тимур 0306
 */
 ////Специализации конструкторов
typedef rational<ll> rational_ll;
////Формат строки - "(sign)num/den"
rational_ll::rational(std::string rat) {
	std::string nuM;
	std::string deN;
	int drob = 0, minus = 0;
	for (int i = 0; rat[i]; i++)
	{
		if (rat[i] == '-') minus++;
		if (rat[i] == '/') drob++;
		if (!(rat[i] >= '0' && rat[i] <= '9' || rat[i] == '/' || rat[i] == '-')) rat.erase(i--, 1);
	}
	if (drob == 0) rat = rat + "/1";
	assert(minus <= 2 && drob <= 1);
	long long i = (rat[0] == '-' ? 1 : 0);
	while (rat[i] != '/') nuM += rat[i++];
	for (i += 1; i < rat.length(); i++) deN += rat[i];
	num = ll(rat[0] == '-' ? '-' + nuM : nuM);
	den = ll(deN);
	assert(den != 0);
	red(*this);
}
//Конструктор из даблов
rational_ll::rational(long double value) {
	ll denum(1), numer(0);
	std::vector<long long> denums;
	uint64_t* bytes = (uint64_t*)&value;
	//Вычисление мантиссы. Первые 52 бита - это мантисса
	for (long long i = 0; i < 52; i++) {
		if ((1LL << i) & *bytes) denums.push_back(pow2(52 - i));
	}
	//Приведение к общему знаменателю
	std::reverse(denums.begin(), denums.end());
	if (denums.size() > 0) {
		numer = ll(1);
		for (int i = 1; i < denums.size(); i++) {
			long long diff = denums[i] / denums[i - 1];
			numer = numer * ll(diff) + ll(1);
		}
		denum = denums[denums.size() - 1];
	}
	//Вычисление экспоненты
	rational<ll> exp;
	int expo = ((*bytes >> 52) & 2047) - 1023; //2047 - 0b11111111111. Это степень экспоненты
	if (expo == -1023) exp = rational<ll>("0/1"); //Случай для нуля
	else if (expo >= 0) exp = rational<ll>(ll(pow2(expo)), ll(1));
	else exp = rational<ll>(ll(1), ll(pow2(-expo)));
	*this = (rational<ll>(numer, denum) + rational<ll>(ll(1))) * exp;
	//Выбор знака
	if (*bytes & (1LL << 63)) num.setSign(true);
}

template <class T>
ll::ll(rational<T>& val)
{
	ll ans = val.getNum() / val.getDen();
	sign = ans.sign;
	num = ans.num;
}

//template<class IND, class COEF>
//bool isnum(rational< polinom<IND, COEF> > val) { return isnum(val); }

/*Overload of << for rational<ll>
template <>std::ostream& operator<< (std::ostream& out, const rational<ll>& val) {
	out << val.num << '/' << val.den;
	return out;
}*/
//Перевод в строку
template <class T>
std::string toString(T val) {
	std::ostringstream string;
	string << val;
	return string.str();
}

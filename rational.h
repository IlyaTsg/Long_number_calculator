#pragma once
#include "Errors.h"

//Òóðóøåâ Òèìóð 0306
template <class T>
class rational
{
    private:
		T num = 0;
		T den = 1;
    public:
		rational<T>() {};	
		rational<T>(T num, T den) : num(num), den(den) {}
		rational<T>(T num) : num(num), den(T(1)) {}
		rational(std::string rat);
		rational<T> operator -() { num = -num; }
		T getNum() { return num; }
		T getDen() { return den; }
		friend bool isnum(rational<T> val) { return (val.den == 1); }
//Øêîäà Ìàðèÿ 0306
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
			if (lval.num > 0 && rval.num < 0) {
				res.num.setSign(true);
				res.den.setSign(false);
			}
			red(res);
			return res;
		}
//Òóðóøåâ Òèìóð 0306
		friend std::ostream& operator<< (std::ostream& out, rational<T>& val) {
			out << val.num;
			out << "/" << val.den;
			return out;
		}
		/*friend std::ostream& operator<< (std::ostream& out, rational<polinom<> >& val) {
			out << val.num << "/" << val.den;
			return out;
		}*/
		//friend std::ostream& operator<< (std::ostream& out, const rational<ll>& val);

		//Reduction
		void static red(rational<T>& to) {
			T frac_gcd = gcd(to.num, to.den);
			to.num = to.num / frac_gcd;
			to.den = to.den / frac_gcd;
			if (to.den < 0 && to.num < 0) {
				to.den = -to.den;
				to.num = -to.num;
			}
		}
//Øêîäà Ìàðèÿ 0306
		//Reduction to a common denominator
		void static comden(rational<T>& lval, rational<T>& rval) 
		{
			T cden = lcm(lval.den, rval.den);
			lval.num = lval.num * (cden / lval.den);
			rval.num = rval.num * (cden / rval.den);
			lval.den = cden;
			rval.den = cden;
		}
	
		friend rational<T> operator -(const rational<T>& lval, const rational<T>& rval) 
		{
			rational<T> res;
			rational<T> rv = rval;
			rational<T> lv = lval;
			comden(rv, lv);
			res.num = rv.num - lv.num;
			res.den = rv.den;
			red(res);
			return res;
		}
};
//Òóðóøåâ Òèìóð 0306
////Ctor specializations
typedef rational<ll> rational_ll;
////String rat format - "(sign)num/den"
rational_ll::rational(std::string rat) 
{
	std::string nuM;
	std::string deN;
	long long i = rat[0] == '-' ? 1 : 0;
	while (rat[i] != '/') nuM += rat[i++];
	for (i += 1; i < rat.length(); i++) deN += rat[i];
	num = ll(rat[0] == '-' ? '-' +nuM : nuM);
	den = ll(deN);
}

template<class IND, class COEF>
bool isnum(rational< polinom<IND, COEF> > val) { return isnum(val); }

/*Overload of << for rational<ll>
template <>std::ostream& operator<< (std::ostream& out, const rational<ll>& val) {
	out << val.num << '/' << val.den;
	return out;
}*/

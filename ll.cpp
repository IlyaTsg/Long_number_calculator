#include "ll.h"

bool operator >(const ll& lval, const ll& rval)
{   if (lval.sign!=rval.sign)
        return lval.sign<rval.sign;
    auto lsize=lval.num.size();
    if (lsize!=rval.num.size())
        return ((lsize>rval.num.size())^lval.sign);
    for (int i=lsize-1; i>-1; i--)
        if (lval.num[i]!=rval.num[i])
            return (lval.num[i]>rval.num[i])^lval.sign;
    return 0;
}

bool operator < (const ll& lval, const ll& rval)
{   return rval>lval;
}

template<typename T>
bool operator >(const T& lval, const ll& rval)
{   return ll(lval)>rval;
}

template<typename T>
bool operator >(const ll& lval, const ll& rval)
{   return lval>ll(rval);
}

template<typename T>
bool operator <(const T& lval, const ll& rval)
{   return ll(lval)<rval;
}

template<typename T>
bool operator <(const ll& lval, const T& rval)
{   return lval<ll(rval);
}

bool operator ==(const ll &lval, const ll &rval){
    if (lval.sign != rval.sign)
        return false;// íå ðàâíû
    else{
        unsigned int len1 = lval.num.size();
        if (len1 != rval.num.size()) return false; // íå ðàâíû
        else{
            for (unsigned int i = len1-1; i>-1; i--)
                if (lval.num[i] != rval.num[i])
                    return false;
            return true;
        }
    }
}

bool operator !=(const ll& lval, const ll& rval){
    return !(lval == rval);
}

template<typename T> 
bool operator >= (const T& lval, const ll& rval)
{   return !(lval>rval);
}

template<typename T>
bool operator >= (const T& lval, const ll& rval)
{   return !(lval<rval);
}

template<typename T>
bool operator <= (const T& lval, const ll& rval)
{   return !(lval>rval);
}

template<typename T>
bool operator <= (const T& lval, const ll& rval)
{   return !(lval>rval);
}

short ll::poz()
{   if (this->num[0] == 0) return 0;
    else if (this->sign) return 1;
    else return 2;
}

std::ostream& operator<< (std::ostream& out, const ll& val)
{
    bool k = false;
    if (val.sign == 1) out << '-';
    for (int i = val.num.size() - 1; i >= 0; i--)
    {
        if (val.num[i] != 0 || k)
        {
            int h = 0;
            for (long long x = val.num[i]; x > 0; x /= 10, h++);
            if (k) for (int i = 0; i < 9 - h; i++) out << '0';
            if (val.num[i] != 0) out << val.num[i];
        }
        if (val.num[i] != 0) k = true;
    }
    return out;
}

void fft(std::vector<std::complex<long double>>& to, bool invert)
{
    int n = to.size();
    if (n == 1) return;
    std::vector<std::complex<long double>> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n; i += 2)
    {
        a0[i / 2] = to[i];
        a1[i / 2] = to[i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);
    long double fi = 2 * power::PI / n * (invert == 1 ? -1 : 1);
    std::complex<long double> p(1), key(cos(fi), sin(fi));
    for (int i = 0; i < n / 2; i++)
    {
        to[i] = a0[i] + p * a1[i];
        to[i + n / 2] = a0[i] - p * a1[i];
        if (invert == 1)
        {
            to[i] /= 2;
            to[i + n / 2] /= 2;
        }
        p *= key;
    }
}

ll ll::operator -() const {
	return ll((!(num.size() == 1 && num[0] == 0) - sign), num);
}
ll ll::abs() const {
	return ll(0, num);
}


ll operator+(const ll& lval, const ll& rval) {
// Creating ll instance with empty vector, because default constructor creates vector with 0 element within
	ll result(0, std::vector<long long>{});
	long long minsize = std::min(lval.num.size(), rval.num.size());
	long long maxsize = std::max(lval.num.size(), rval.num.size());
/*
*After addition of two elements programm adds first 9 elements to resultant vector and divides sum by 10^9 for sake of overflow tracing,
*because if overflow happens this division's result would be 1, which we will add to next element, otherwise this division's result would be 0
*/
	if (lval.sign == rval.sign) {
		long long sum = 0;
		for (int i = 0; i < minsize; i++) {
			sum += lval.num[i] + rval.num[i];
			result.num.push_back(sum % power::mod);
			sum /= power::mod;
		}
//Addition of remainding larger vector's elemenets, which weren't involved in addition.
		if (lval.num.size() > rval.num.size()) {
			for (int i = minsize; i < maxsize; i++) {
				sum += lval.num[i];
				result.num.push_back(sum % power::mod);
				sum /= power::mod;
			}
		}
		else if (lval.num.size() < rval.num.size()) {
			for (int i = minsize; i < maxsize; i++) {
				sum += rval.num[i];
				result.num.push_back(sum % power::mod);
				sum /= power::mod;
			}
		}
//If after all those calculations programm got left 1, programm adds this 1 to next new rank
		if (sum) result.num.push_back(1);
		result.sign = lval.sign;
	}
//If the signs of operands don't match, programm calculate substraction.
	else {
		long long sub = 0;
//Choosing from which ll instance we substract another one
		if (lval == -rval) {
			result = ll();
		}
		else if (lval.abs() >= rval.abs())
			for (int i = 0; i < minsize; i++) {
				sub = power::mod * (lval.num[i] < rval.num[i]) + lval.num[i] - rval.num[i] - sub;
				result.num.push_back(sub);
//Check for borrowing 1 from higher rank
				sub = (lval.num[i] < rval.num[i]) ? 1 : 0;
			}
		else {
			for (int i = 0; i < minsize; i++) {
				sub = power::mod * (rval.num[i] < lval.num[i]) + rval.num[i] - lval.num[i] - sub;
				result.num.push_back(sub);
//Check for borrowing 1 from higher rank
				sub = (rval.num[i] < lval.num[i]) ? 1 : 0;
			}
//Addition of remainding larger vector's elemenets, which weren't involved in addition, and if necessary we borrow 1 form higher ranks
		}
		if (lval.abs() >= rval.abs()) {
			for (int i = minsize; i < maxsize; i++) {
				sub = power::mod * (lval.num[i] < sub) + lval.num[i] - sub;
				if (sub > lval.num[i]) sub = 1;
				result.num.push_back(sub);
			}
		}
		else {
			for (int i = minsize; i < maxsize; i++) {
				sub = power::mod * (rval.num[i] < sub) + rval.num[i] - sub;
				if (sub > rval.num[i]) sub = 1;
				result.num.push_back(sub);
			}
		}
//Deleting insignificant 0 from end of vector
		if (result.num.size() > 1 && result.num[result.num.size() - 1] == 0) result.num.pop_back();
		result.sign = lval.abs() >= rval.abs() ? lval.sign : rval.sign;
	}
	return result;
}
ll operator -(const ll& lval, const ll& rval)
{
	ll result;
	result = lval + (-rval);
	return result;
};

ll operator *(const ll& lval, const ll& rval)
{
    std::vector<long long> l_val, r_val;
    for (int i = 0; i < std::max(lval.num.size(), rval.num.size()); i++)
    {
        if(i < static_cast<int>(lval.num.size()))
        {
            l_val.push_back(lval.num[i] % 1000);
            l_val.push_back(lval.num[i] / 1000 % 1000);
            l_val.push_back(lval.num[i] / 1000000);
        }
        if (i < static_cast<int>(rval.num.size()))
        {
            r_val.push_back(rval.num[i] % 1000);
            r_val.push_back(rval.num[i] / 1000 % 1000);
            r_val.push_back(rval.num[i] / 1000000);
        }
    }
    int n = 1;
    for (; n <= static_cast<int>(std::max(l_val.size(), r_val.size())); n <<= 1);
    n <<= 1;
    l_val.resize(n);
    r_val.resize(n);
    std::vector< std::complex<long double> > flval(l_val.begin(), l_val.end()), frval(r_val.begin(), r_val.end());
    fft(flval, false);
    fft(frval, false);
    for (int i = 0; i < n; i++) flval[i] *= frval[i];
    fft(flval, true);
    std::vector<long long> ans(n), ansy;
    for (int i = 0; i < n; i++) ans[i] = static_cast<long long>(flval[i].real() + 0.5);
    for (int i = 0; i < n - 1; i++)
    {
        ans[i + 1] += ans[i] / 1000;
        ans[i] %= 1000;
    }
    for (int i = 0; i < n; i++)
    {
        if (i % 3 == 0) ansy.push_back(ans[i]);
        else ansy[i / 3] += pow(1000, i % 3) * ans[i];
    }
    return ll(lval.sign^rval.sign, ansy);
}

ll::ll(): sign{ false }, num{ 0 }{};
ll::ll(int to): sign{ to < 0 }{
    if (sign) to *= -1;
    num.push_back(to % power::mod);
    num.push_back(to / power::mod);
};
ll::ll(long long to): sign{ to < 0 }{
    if (sign) to *= -1;
    num.push_back(to % power::mod);
    to /= power::mod;
    num.push_back(to % power::mod);
    num.push_back(to / power::mod);
};
ll::ll(std::string to){
    int digit = 0, degree = 1;
    if(sign=(to[0]=='-')) to.erase(0,1);
    int len = to.length();
    for(int i=len-1; i>=0; i--){
        digit = digit + ((int)to[i]-48)*degree;
        degree *= 10;
        if(!((len-i)%9)||!i){
            num.push_back(digit);
            digit = 0;
            degree = 1;
        }
    }
};
ll::ll(bool sigN, std::vector<long long> nuM): sign{ sigN }, num{ nuM }{};

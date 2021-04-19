#include "ll.h"

ll ll::operator -() const {
	return ll((!(num.size() == 1 && num[0] == 0) - sign), num);
}
ll ll::abs() const {
	return ll(0, num);
}


ll operator+(const ll& lval, const ll& rval) {
// Creating ll instance with empty vector, because default constructor creates vector with 0 element within
	ll result(0, std::vector<long long>{});
	long long minsize = min(lval.num.size(), rval.num.size())
	long long maxsize = max(lval.num.size(), rval.num.size())
/*
* After addition of two elements programm adds first 9 elements to resultant vector and divides sum by 10^9 for sake of overflow tracing,
*because if overflow happens this division's result would be 1, which we will add to next element, otherwise this division's result would be 0
*/
	if (lval.sign == rval.sign) {
		long long sum = 0;
		for (int i = 0; i < minsize; i++) {
			sum += lval.num[i] + rval.num[i];
			result.num.push_back(sum % mod);
			sum /= mod;
		}
//Addition of remainding larger vector's elemenets, which weren't involved in addition.
		if (lval.num.size() > rval.num.size()) {
			for (int i = minsize; i < maxsize; i++) {
				sum += lval.num[i];
				result.num.push_back(sum % mod);
				sum /= mod;
			}
		}
		else if (lval.num.size() < rval.num.size()) {
			for (int i = minsize; i < maxsize; i++) {
				sum += rval.num[i];
				result.num.push_back(sum % mod);
				sum /= mod;
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
				sub = mod * (lval.num[i] < rval.num[i]) + lval.num[i] - rval.num[i] - sub;
				result.num.push_back(sub);
//Check for borrowing 1 from higher rank
				sub = (lval.num[i] < rval.num[i]) ? 1 : 0;
			}
		else {
			for (int i = 0; i < minsize; i++) {
				sub = mod * (rval.num[i] < lval.num[i]) + rval.num[i] - lval.num[i] - sub;
				result.num.push_back(sub);
//Check for borrowing 1 from higher rank
				sub = (rval.num[i] < lval.num[i]) ? 1 : 0;
			}
//Addition of remainding larger vector's elemenets, which weren't involved in addition, and if necessary we borrow 1 form higher ranks
		}
		if (lval.abs() >= rval.abs()) {
			for (int i = minsize; i < maxsize; i++) {
				sub = mod * (lval.num[i] < sub) + lval.num[i] - sub;
				if (sub > lval.num[i]) sub = 1;
				result.num.push_back(sub);
			}
		}
		else {
			for (int i = minsize; i < maxsize; i++) {
				sub = mod * (rval.num[i] < sub) + rval.num[i] - sub;
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


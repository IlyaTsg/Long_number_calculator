#include "ll.h"

ll ll::operator -() const {
	return ll(true - sign, num);
}
ll ll::abs() const {
	return ll(0, num);
}


ll operator+(const ll& lval, const ll& rval) {
	//Создаём объект с пустым вектором, т.к. дефолтный конструктор создаёт объект с вектором, в котором уже содержится 0
	ll result(0, std::vector<long long>{});
	long long minsize = lval.num.size() < rval.num.size() ? lval.num.size() : rval.num.size();//Тернарные операторы, т.к. 
	long long maxsize = lval.num.size() < rval.num.size() ? rval.num.size() : lval.num.size();//у меня чому-то не работает  min и max. Потом заменю
/*
*В сложении мы идём сначала циклом по минимальной длине вектора, складывая соответствующие их эл-ты. После сложения мы добавляем первые 9 цифр этой суммы
*в элемент результирующего вектора, а затем эту сумму мы делим на миллиард. Это сделано с целью отслеживания переполнения, т.е. если бы мы вышли за предел в
*9 цифр, то это деление дало бы единицу, а если не вышли, то 0.
*/
	if (lval.sign == rval.sign) {
		long long sum = 0;
		for (int i = 0; i < minsize; i++) {
			sum += lval.num[i] + rval.num[i];
			result.num.push_back(sum % mod);
			sum /= mod;
		}
		//Добавление оставшихся разрядов, которые не были задействованы в сложении, если размерности векторов не совпадают
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
		//Если после всего осталась единица, то добавляем её в следющий разряд
		if (sum) result.num.push_back(1);
		result.sign = lval.sign;
	}
	/*
	*Если знаки операндов разные, то происходит вычитание. Общий прицнип схож со сложением, т.е. так же сначала вычитаем по минимальной
	*длине вектора, а затем добавляем оставшиеся эл-ты бОльшего вектора, если таковой имеется, и занимаем из старших разрядом. Асимптотика та же.
	*/
	else {
		long long sub = 0;

		//Выбираем число из которого будем вычитать
		if (lval == -rval) {
			result = ll();
		}
		else if (lval.abs() >= rval.abs())
			for (int i = 0; i < minsize; i++) {
				sub = mod * (lval.num[i] < rval.num[i]) + lval.num[i] - rval.num[i] - sub;
				result.num.push_back(sub);
				sub = (lval.num[i] < rval.num[i]) ? 1 : 0;
			}
		else {
			for (int i = 0; i < minsize; i++) {
				sub = mod * (rval.num[i] < lval.num[i]) + rval.num[i] - lval.num[i] - sub;
				result.num.push_back(sub);
				sub = (rval.num[i] < lval.num[i]) ? 1 : 0;
			}
			//Добавляем оставшиеся разряды и, если нужно, занимаем единицу из старших разрядов
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
		//Удаляем незначащий ноль с конца
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


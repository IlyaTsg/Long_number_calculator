#include "ll.h"

namespace power {
	const long long mod = 1000000000;
}
using namespace power;

ll::ll() {
	sign = 0;
	num = std::vector<long long>{ 0 };
};
ll::ll(bool sigN, std::vector<long long> vec) {
	num = vec;
	sign = sigN;
}
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


int main() {
	std::vector<long long> a = { 1 };
	std::vector<long long> b = { 0, 0, 1 };
	std::vector<long long> c = { 999999999, 999999999, 999999999, 999999999, 1 };
	std::vector<long long> d = { 999999999, 999999991, 000000000, 999999998, 1 };
	std::vector<long long> e = { 0 };
	std::vector<long long> b1 = { 999999999, 123456789, 123456789 };
	std::vector<long long> c1 = { 0, 999999999, 0, 999999999, 1 };

	ll t(false, a);
	ll t2(false, b);
	ll t3(false, c);
	ll t4(false, d);
	ll t5(false, e);
	ll t6(false, b1);
	ll t7(false, c1);

	// Тесты//

	ll test = t3 + t4;
	for (int i = 0; i < test.getVec().size(); i++) std::cout << test.getVec()[i] << " ";
	std::cout << std::endl << "sign is " << test.getSign() << "\n";
	std::cout << "999999998 999999991 0 999999998 3 Expected\n Sign is 0" << "\n";
	ll test2 = t4 + t5;
	for (int i = 0; i < test2.getVec().size(); i++) std::cout << test2.getVec()[i] << " ";
	std::cout << std::endl << "sign is " << test2.getSign() << "\n";
	std::cout << "999999999 999999991 0 999999998 1 Expected\n Sign is 0" << "\n";
	ll test3 = t5 - t2;
	for (int i = 0; i < test3.getVec().size(); i++) std::cout << test3.getVec()[i] << " ";
	std::cout << std::endl << "sign is " << test3.getSign() << "\n";
	std::cout << "0 0 1 Expected\n Sign is 1" << "\n";
	ll test4 = t2 - t5;
	for (int i = 0; i < test4.getVec().size(); i++) std::cout << test4.getVec()[i] << " ";
	std::cout << std::endl << "sign is " << test4.getSign() << "\n";
	std::cout << "0 0 1 Expected\n Sign is 0" << "\n";
	ll test5 = -t4 - (-t3);
	for (int i = 0; i < test5.getVec().size(); i++) std::cout << test5.getVec()[i] << " ";
	std::cout << std::endl << "sign is " << test5.getSign() << "\n";
	std::cout << "0 8 999999999 1 Expected\n Sign is 0" << "\n";
	ll test6 = t7 - t6;
	for (int i = 0; i < test6.getVec().size(); i++) std::cout << test6.getVec()[i] << " ";
	std::cout << std::endl << "sign is " << test6.getSign() << "\n";
	std::cout << "1 876543209 876543211 999999998 1 Expected\n Sign is 0" << "\n";
	ll test0 = t7 - t7;
	for (int i = 0; i < test0.getVec().size(); i++) std::cout << test0.getVec()[i] << " ";
	std::cout << "sign is " << test0.getSign() << "\n";
	std::cout << "0 Expected\n Sign is 0\n";
	ll test7 = ll(false, std::vector<long long>{0, 0, 0, 0, 0, 0, 0, 101010101, 1}) - ll(false, std::vector<long long>{0, 0, 0, 0, 0, 0, 101010101, 0, 1});
	for (int i = 0; i < test7.getVec().size(); i++) std::cout << test7.getVec()[i] << " ";
	std::cout << "sign is " << test7.getSign() << "\n";
	std::cout << "0 0 0 0 0 0 898989899  101010100 Expected\n Sign is 0" << "\n";
	ll test8 = ll(false, std::vector<long long>{500000000}) + ll(false, std::vector<long long>{500000000});
	for (int i = 0; i < test8.getVec().size(); i++) std::cout << test8.getVec()[i] << " ";
	std::cout << "sign is " << test8.getSign() << "\n";
	std::cout << "0 1 Expected\n Sign is 0" << "\n";
	ll test9 = ll(false, std::vector<long long>{0}) + ll(false, std::vector<long long>{0});
	for (int i = 0; i < test9.getVec().size(); i++) std::cout << test9.getVec()[i] << " ";
	std::cout << "sign is " << test9.getSign() << "\n";
	std::cout << "0 Expected\n Sign is 0" << "\n";
	ll test10 = ll(false, std::vector<long long>{0, 3}) - ll(false, std::vector<long long>{1});
	for (int i = 0; i < test10.getVec().size(); i++) std::cout << test10.getVec()[i] << " ";
	std::cout << "sign is " << test10.getSign() << "\n";
	std::cout << "999999999 2 Expected\n Sign is 0" << "\n";
};

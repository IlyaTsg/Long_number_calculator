#pragma once
#include "Errors.h"

template <class T> rational;

void flush(std::vector<long long>& g)
{
    int k = g.size() - 1;
    if (k <= 0) return;
    while (k > 0 && g[k] == 0) k--;
    g.resize(k + 1);
}

int log2(long long n)
{
    int s = 0;
    for (int i = 1; i <= n; i *= 2, s++);
    return s;
}

class ll
{
private:
    std::vector<long long> num;  //Вектор цифр в 10^9-ичной системе счисления в обратном порядке
    bool sign;              //0 - плюс, 1 - минус

public:
    //Конструкторы
    ll() : sign{ false }, num({ 0 }){};     //Пустой
    //По знаку и значению
    ll(bool sig, std::vector<long long> nu) : sign(sig), num(nu) {}

    ll(int to);                             //По числу
    ll(long long to);
    
    ll(std::string to);                     //По строке


    void NaN_to_NULL() { if (num.size() == 1 && num[0] == 0) sign = 0; }      //Замена значения NaN на обыкновенный 0

    std::vector<long long> getVec() { return num; }                           //Геттеры
    bool getSign() { return sign; }
    
    void setSign(bool val) { sign = val; }                                    //Сеттеры

    //Унарный минус
    ll operator -() const { return ll((!(num.size() == 1 && num[0] == 0) - sign), num); }

    //Операторы сравнения, реализованные сначала для собственного типа данных, затем для литералов других типов данных
    friend bool operator ==(const ll& lval, const ll& rval);
    template<class T> friend bool operator ==(const T& lval, const ll& rval) { return (ll(lval) == rval); }
    template<class T> friend bool operator ==(const ll& lval, const T& rval) { return (lval == ll(rval)); }

    friend bool operator > (const ll& lval, const ll& rval);
    template <class T> friend bool operator > (const T& lval, const ll& rval) { return (ll(lval) > rval); }
    template <class T> friend bool operator > (const ll& lval, const T& rval) { return (lval > ll(rval)); }

    friend bool operator < (const ll& lval, const ll& rval) { return rval > lval; }
    template <class T> friend bool operator < (const ll& lval, const T& rval) { return (lval < ll(rval)); }
    template <class T> friend bool operator < (const T& lval, const ll& rval) { return (ll(lval) < rval); }

    friend bool operator !=(const ll& lval, const ll& rval) { return !(lval == rval); }
    template <class T> friend bool operator !=(const T& lval, const ll& rval) { return (ll(lval) != rval); }
    template <class T> friend bool operator !=(const ll& lval, const T& rval) { return (lval != ll(rval)); }

    friend bool operator >=(const ll& lval, const ll& rval) { return !(lval < rval); }
    template <class T> friend bool operator >=(const T& lval, const ll& rval) { return !(ll(lval) < rval); }
    template <class T> friend bool operator >=(const ll& lval, const T& rval) { return !(lval < ll(rval)); }

    friend bool operator <=(const ll& lval, const ll& rval) { return !(lval > rval); }
    template <class T> friend bool operator <=(const T& lval, const ll& rval) { return !(ll(lval) > rval); }
    template <class T> friend bool operator <=(const ll& lval, const T& rval) { return !(lval > ll(rval)); }


    friend ll operator +(const ll& lval, const ll& rval);       //Z-6
    template <class T> friend ll operator +(const T& lval, const ll& rval) { return ll(lval) + rval; }
    template <class T> friend ll operator +(const ll& lval, const T& rval) { return lval + ll(rval); }

    friend ll operator -(const ll& lval, const ll& rval) { return (lval + (-rval)); }       //Z-7
    template <class T> friend ll operator -(const T& lval, const ll& rval) { return ll(lval) - rval; }
    template <class T> friend ll operator -(const ll& lval, const T& rval) { return lval - ll(rval); }

    friend ll operator %(const ll& lval, const ll& rval);       //Z-10
    friend long long operator %(const ll& l_val, int r_val);
    friend ll operator *(const ll& lval, const ll& rval);       //Z-8
    friend ll operator *(const ll& lval, int rval);
    friend ll operator *(int lval, const ll& rval) { return (rval * lval); }
    friend ll operator /(const ll& lval, const ll& rval);       //Z-9
    friend std::ostream& operator<< (std::ostream& out, const ll& val);

    ll abs() const { return ll(0, num); }               //Z-1
    short poz();            //Z-2
    ll rsign();             //Z-3

    friend ll divby2(ll val);
    int len()
    {
        int s = (num.size() - 1) * 9, h = 0;
        for (int x = num[num.size() - 1]; x != 0; x /= 10, h++);
        return s + h;
    }
};

namespace power         //Пространство имен для констант
{
    const int mod = 1'000'000'000;
    const double PI = 3.141592653589793238462643383279;
}

//Перегрузка потокового ввода
std::istream& operator>> (std::istream& in, ll& val)
{
    std::string key;
    std::getline(in, key);
    val = ll(key);
    return in;
}

/**\brief îïåðàòîð > äëÿ äâóõ ll ÷èñåë
 * Ñðàâíèâàåò ïîñëåäîâàòåëüíî ñíà÷àëà çíàêè ÷èñåë, ïîòîì èõ äëèíó, ïîòîì íà÷èíàÿ ñ íàèáîëüøåãî ñðàâíèâàåò èõ ïîñèìâîëüíî
 * Íå çàâèñèò îò äðóãèõ ôóíêöèé è îïåðàòîðîâ
 * Àñèìïòîòèêà ïî âðåìåíè - O(n), êîíñòàíòà àñèìïòîòèêè 2
 * Àñèìïòîòèêà ïî ïàìÿòè - O(1), êîíñòàíòà àñèìïòîòèêè 2
 * \param lval const ll& ëåâîå ÷èñëî
 * \param rval const ll& ïðàâîå ÷èñëî
 * \return bool true, åñëè ëåâîå áîëüøå ïðàâîãî, èíà÷å false
 */
bool operator >(const ll& lval, const ll& rval)
{
    if (lval.sign != rval.sign) return (lval.sign < rval.sign);
    int lsize = lval.num.size();
    if (lsize != rval.num.size()) return ((lsize > rval.num.size()) ^ lval.sign);
    for (int i = lsize - 1; i >= 0; i--) if (lval.num[i] != rval.num[i]) return ((lval.num[i] > rval.num[i]) ^ lval.sign);
    return false;
}
/**\brief îïåðàòîð < äëÿ äâóõ ll ÷èñåë
 * Ñðàâíèâàåò ïîñëåäîâàòåëüíî ñíà÷àëà çíàêè ÷èñåë, ïîòîì èõ äëèíó, ïîòîì íà÷èíàÿ ñ íàèáîëüøåãî ñðàâíèâàåò èõ ïîñèìâîëüíî
 * Çàâèñèò îò îïåðàòîðîâ > è !=
 * Àñèìïòîòèêà ïî âðåìåíè - O(n), êîíñòàíòà àñèìïòîòèêè 2
 * Àñèìïòîòèêà ïî ïàìÿòè - O(1), êîíñòàíòà àñèìïòîòèêè 2
 * \param lval const ll& ëåâîå ÷èñëî
 * \param rval const ll& ïðàâîå ÷èñëî
 * \return bool true, åñëè ëåâîå ìåíüøå ïðàâîãî, èíà÷å false
 */

//Частный случай остатка от деления, для int делителя
long long operator %(const ll& l_val, int r_val)
{
    assert(r_val != 0);
    long long sum = 0;
    for (long long i = 0, n = l_val.num.size(), p = 1; i < n; i++)
    {
        sum = (sum + l_val.num[i] * p) % r_val;
        p = p * power::mod % r_val;
    }
    return sum % r_val;
}

//Градусные тригонометрические функции
long double sin(ll a)
{
    long double key = static_cast<long double>(a % 360) / 180 * power::PI;
    return sin(key);
}

long double cos(ll a)
{
    long double key = static_cast<long double>(a % 360) / 180 * power::PI;
    return cos(key);
}

long double tg(ll a)
{
    long double key = static_cast<long double>(a % 360) / 180 * power::PI;
    return sin(key) / cos(key);
}

long double ctg(ll a)
{
    long double key = static_cast<long double>(a % 360) / 180 * power::PI;
    return cos(key) / sin(key);
}

//Частный случай умножения, для int множителя, реализован столбик
ll operator *(const ll& lval, int rval)
{
    bool new_sign = (lval.sign ^ (rval < 0));
    if (rval < 0) rval *= -1;
    std::vector<long long> tmp = lval.num;
    long long sum = 0, r = rval;
    for (int i = 0, n = tmp.size(); i < n; i++)
    {
        tmp[i] *= r;
        tmp[i] += sum;
        sum = tmp[i] / power::mod;
        tmp[i] %= power::mod;
    }
    if (sum != 0) tmp.push_back(sum);
    flush(tmp);
    ll ans = ll(new_sign, tmp);
    ans.NaN_to_NULL();
    return ans;
}

//Поциферное сравнение двух чисел
bool operator ==(const ll& lval, const ll& rval)
{
    int len1 = lval.num.size();
    if (len1 != rval.num.size() || lval.sign != rval.sign) return false; // íå ðàâíû
    for (int i = 0; i < len1; i++) if (lval.num[i] != rval.num[i]) return false;
    return true;
}

//Положительное/Отрицательное/Ноль число
short ll::poz()
{
    if (num.size() == 1 && num[0] == 0) return 0;
    return (2 - sign);
}

//Перегрузка потокового вывода
std::ostream& operator<< (std::ostream& out, const ll& val)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n = val.num.size();
    if (val.num.size() == 1 && val.num[0] == 0)
    {
        out << 0;
        return out;
    }
    bool k = false;
    if (val.sign == 1) out << '-';
    for (int i = val.num.size() - 1; i >= 0; i--)
    {
        if (n - i != 1)
        {
            int h = 0;
            for (long long x = val.num[i]; x > 0; x /= 10, h++);
            for (int j = 0; j < 9 - h; j++) out << '0';
        }
        if (val.num[i] != 0) out << val.num[i];
    }
    return out;
}

//Алгоритм быстрого преобразования Фурье
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


ll operator+(const ll& lval, const ll& rval) {
    std::vector<long long> lvec = lval.num;
    std::vector<long long> rvec = rval.num;
    lvec.size() > rvec.size() ? rvec.resize(lvec.size(), 0) : lvec.resize(rvec.size(), 0);
    ll result(0, std::vector<long long>(lvec.size() + 1, 0));
    if (lval.abs() < rval.abs()) std::swap(lvec, rvec);
    bool sf = (rval.sign != lval.sign); //Sign Flag
    bool lf; //Less than Flag
    for (int i = 0; i < lvec.size(); i++) 
    {
        lf = (lvec[i] < rvec[i]);
        // "(1 - 2*static_cast<long long>(sf)) * rvec[i]" statement is responsible for checking type of operation, i.e.
        //  substraction or addition. If sf = 1 (i.e. signs of operands aren't equal) programm calclulate this statement to 1-2 = -1, and so
        //	we got minus sign for rvec[i]
        //	"power::mod*sf*lf + lvec[i]" statement is responsible for borrowing 1 from higher rank. If sf = 1 (substraction) and lf = 1 (substraction from 
        //	lesser element) than we multiply it b 10^9 (borrowing 1 from higher rank)
        result.num[i] += power::mod * sf * lf + lvec[i] + (1 - 2 * static_cast<long long>(sf)) * rvec[i];
        lf = (lvec[i] < result.num[i]);
        //	This block is responsible for borrowing from higher rank in case of substraction or for addition 1 to higher rank in case of addition.
        //	"(result.num[i] / power::mod)" statement gives us 1 if we got more than 9 digits, and 0 if less than 9 digits (that's check for addition overflow).
        //	"(lf && sf)" statement if sf = 1 (substraction operation) and lf (substraction from lesser element) gives us -1 (that's check for borrowing from higher ranks)
        result.num[i + 1] += (result.num[i] / power::mod) - (lf && sf);
        result.num[i] %= power::mod;
    }
    result.sign = sf * (lval.abs() < rval.abs()) ? rval.sign : lval.sign;
    flush(result.num);
    result.NaN_to_NULL();
    return result;
}

ll operator *(const ll& lval, const ll& rval)
{
    std::vector<long long> l_val, r_val;
    for (long long i = 0; i < std::max(lval.num.size(), rval.num.size()); i++)
    {
        if (i < static_cast<int>(lval.num.size()))
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
        else ansy[i / 3] += static_cast<long long>(pow(1000, i % 3)) * ans[i];
    }
    flush(ansy);
    ll a = ll(lval.sign ^ rval.sign, ansy);
    a.NaN_to_NULL();
    return a;
}

ll::ll(int to) : sign{ to < 0 } {
    if (sign) to *= -1;
    num.push_back(to % power::mod);
    num.push_back(to / power::mod);
    flush(num);
}
ll::ll(long long to) : sign{ to < 0 } {
    if (sign) to *= -1;
    num.push_back(to % power::mod);
    to /= power::mod;
    num.push_back(to % power::mod);
    num.push_back(to / power::mod);
    flush(num);
}
ll::ll(std::string to)
{
    int digit = 0, degree = 1;
    sign = (to[0] == '-');
    if (sign) to.erase(0, 1);
    for (int len = to.length(), i = len - 1; i >= 0; i--)
    {
        while (i && to[i] == static_cast<char>(39))
        {
            to.erase(i, 1);
            i--;
            len--;
        }        digit = digit + (static_cast<long long>(to[i]) - 48) * degree;
        degree *= 10;
        if (!((len - i) % 9) || !i)
        {
            num.push_back(digit);
            digit = 0;
            degree = 1;
        }
    }
    flush(num);
}

ll divby2(ll val)
{
    //std::cout << val.abs() << std::endl;
    if (val.num.size() == 1 && val.num[0] < 2)
    {
        //std::cout << "Gospode\n";
        return ll();
    }
    std::vector<long long> new_val;
    //std::cout << val.num.size() << std::endl;
    for (int i = 0, n = val.num.size(); i < n; i++)
    {
        if (!(i == n - 1 && val.num[i] < 2)) new_val.push_back(val.num[i] / 2);
        if (i) new_val[i - 1] = new_val[i - 1] + val.num[i] % 2 * (power::mod / 2);
        //std::cout << new_val[i] << std::endl;
    }
    flush(new_val);
    return ll(val.sign, new_val);
}

ll operator /(const ll& lval, const ll& rval)
{
    assert(rval != 0);
    bool new_sign = (lval.sign ^ rval.sign);
    ll l_val = lval.abs(), r_val = rval.abs(), l, r = l_val + 1, new_val, one(1), g = r - l - 1;
    //std::cout << l << ' ' << r << std::endl;
    while (r - l > 1)
    {
        new_val = divby2(l + r);
        if (r_val * new_val > l_val) r = new_val;
        else l = new_val;
        //std::cout << r - l << " > " << one << ' ' << ((r - l) > one) << ' ' << r << ' ' << l << ' ' << new_val << std::endl;
        g = r - l - 1;
    }
    flush(l.num);
    l.sign = new_sign;
    l.NaN_to_NULL();
    return l;
}

ll operator %(const ll& lval, const ll& rval) 
{
    assert(rval != 0);
    ll ans = lval - lval / rval * rval;
    ans.NaN_to_NULL();
    return ans;
}
//The repair is over

// Илья Цыганков гр. 0306
template <class Type>
Type gcd(Type a, Type b) { return (b == 0 ? a : gcd(b, a % b)); }

// Илья Цыганков гр. 0306
template <class Type>
Type lcm(Type a, Type b) { return a / gcd(a, b) * b; }

// Илья Цыганков гр. 0306
ll fact(int digit)
{
    assert(digit >= 0);
    ll tmp = 1;
    for (int i = 2; i <= digit; i++) tmp = tmp * i;
    return tmp;
}

// Илья Цыганков гр. 0306
ll fib(int digit)
{
    assert(digit >= 0);
    static std::map<long long, ll> fibm;
    if (fibm[digit] == 0) {
        fibm[0] = 0;
        fibm[1] = 1;
        fibm[2] = 1;
        fibm[3] = 2;
        if (digit < 4) return fibm[digit];
        else if (digit % 2) fibm[digit] = fib((digit - 1) / 2 + 1) * fib((digit - 1) / 2 + 2) - fib((digit - 1) / 2) * fib((digit - 1) / 2 - 1);
        else fibm[digit] = fib(digit / 2) * (fib(digit / 2 - 1) + fib(digit / 2 + 1));
    }
    return fibm[digit];
}

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <complex>

namespace power
{
    const int mod = 1'000'000'000;
    const double PI = 3.141592653589793238462643383279;
}

void flush(std::vector<long long>& g)
{
    int k = g.size() - 1;
    if (k <= 0) return;
    while (k > 0 && g[k] == 0) k--;
    g.resize(k + 1);
}

class ll
{
private:
    std::vector<long long> num;  //Âåêòîð öèôð
    bool sign;              //0 - ïëþñ, 1 - ìèíóñ

public:
    ll() : sign{ false }, num({ 0 }){};
    ll(bool sig, std::vector<long long> nu) : sign(sig), num(nu) {}
    ll(int to);
    ll(long long to);
    ll(std::string to);

    std::vector<long long> getVec() { return num; }
    bool getSign() { return sign; }

    ll operator -() const { return ll((!(num.size() == 1 && num[0] == 0) - sign), num); }

    friend bool operator ==(const ll& lval, const ll& rval);
    template<typename T> friend bool operator ==(const T& lval, const ll& rval) { return (ll(lval) == rval); }
    template<typename T> friend bool operator ==(const ll& lval, const T& rval) { return (lval == ll(rval)); }

    friend bool operator > (const ll& lval, const ll& rval);
    template <typename T> friend bool operator > (const T& lval, const ll& rval) { return (ll(lval) > rval); }
    template <typename T> friend bool operator > (const ll& lval, const T& rval) { return (lval > ll(rval)); }

    friend bool operator < (const ll& lval, const ll& rval) { return rval > lval; }
    template <typename T> friend bool operator < (const ll& lval, const T& rval) { return (lval < ll(rval)); }
    template <typename T> friend bool operator < (const T& lval, const ll& rval) { return (ll(lval) < rval); }

    friend bool operator !=(const ll& lval, const ll& rval) { return !(lval == rval); }
    template <typename T> friend bool operator !=(const T& lval, const ll& rval) { return !(ll(lval) != rval); }
    template <typename T> friend bool operator !=(const ll& lval, const T& rval) { return !(lval != ll(rval)); }
    
    friend bool operator >=(const ll& lval, const ll& rval) { return !(lval < rval); }
    template <typename T> friend bool operator >=(const T& lval, const ll& rval) { return !(ll(lval) < rval); }
    template <typename T> friend bool operator >=(const ll& lval, const T& rval) { return !(lval < ll(rval)); }

    friend bool operator <=(const ll& lval, const ll& rval) { return !(lval > rval); }
    template <typename T> friend bool operator <=(const T& lval, const ll& rval) { return !(ll(lval) > rval); }
    template <typename T> friend bool operator <=(const ll& lval, const T& rval) { return !(lval > ll(rval)); }

    //friend bool operator = (ll& val) { sign = val.sign; num = val.num; }

    friend ll operator +(const ll& lval, const ll& rval);       //Z-6
    friend ll operator -(const ll& lval, const ll& rval) { return (lval + (-rval)); }       //Z-7
    friend ll operator %(const ll& lval, const ll& rval);       //Z-10
    friend ll operator *(const ll& lval, const ll& rval);       //Z-8
    friend ll operator /(const ll& lval, const ll& rval);       //Z-9
    friend std::ostream& operator<< (std::ostream& out, const ll& val);

    ll abs() const { return ll(0, num); }               //Z-1
    short poz();            //Z-2
    ll rsign();             //Z-3

    ll fact();              //Ôàêòîðèàë
    //Ïðî÷èå çàäà÷è äëÿ öåëûõ ÷èñåë
    friend ll divby2(ll val);
};

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

bool operator ==(const ll& lval, const ll& rval) 
{
    int len1 = lval.num.size();
    if (len1 != rval.num.size() || lval.sign != rval.sign) return false; // íå ðàâíû
    for (int i = 0; i < len1; i++) if (lval.num[i] != rval.num[i]) return false;
    return true;
}

short ll::poz()
{
    if (num.size() == 1 && num[0] == 0) return 0;
    return (2 - sign);
}

std::ostream& operator<< (std::ostream& out, const ll& val)
{
    if (val.num.size() == 1 && val.num[0] == 0)
    {
        out << 0;
        return out;
    }
    bool k = false;
    if (val.sign == 1) out << '-';
    for (int i = val.num.size() - 1; i >= 0; i--)
    {
        if (k || val.num[i] != 0)
        {
            int h = 0;
            if (k)
            {
                for (long long x = val.num[i]; x > 0; x /= 10, h++);
                if (k) for (int j = 0; j < 9 - h; j++) out << '0';
            }
            out << val.num[i];
            k = true;
        }
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

ll operator+(const ll& lval, const ll& rval) {
    // creating ll instance with empty vector, because default constructor creates vector with 0 element within
    ll result(0, std::vector<long long>{});
    long long minsize = std::min(lval.num.size(), rval.num.size());
    long long maxsize = std::max(lval.num.size(), rval.num.size());
    /*
    * after addition of two elements programm adds first 9 elements to resultant vector and divides sum by 10^9 for sake of overflow tracing,
    *because if overflow happens this division's result would be 1, which we will add to next element, otherwise this division's result would be 0
    */
    if (lval.sign == rval.sign) 
    {
        long long sum = 0;
        for (int i = 0; i < minsize; i++) 
        {
            sum += lval.num[i] + rval.num[i];
            result.num.push_back(sum % power::mod);
            sum /= power::mod;
        }
        //addition of remainding larger vector's elemenets, which weren't involved in addition.
        if (lval.num.size() > rval.num.size()) 
        {
            for (int i = minsize; i < maxsize; i++) 
            {
                sum += lval.num[i];
                result.num.push_back(sum % power::mod);
                sum /= power::mod;
            }
        }
        else if (lval.num.size() < rval.num.size()) 
        {
            for (int i = minsize; i < maxsize; i++) 
            {
                sum += rval.num[i];
                result.num.push_back(sum % power::mod);
                sum /= power::mod;
            }
        }
        //if after all those calculations programm got left 1, programm adds this 1 to next new rank
        if (sum) result.num.push_back(1);
        result.sign = lval.sign;
    }//if the signs of operands don't match, programm calculate substraction.
    else 
    {
        long long sub = 0;
        //choosing from which ll instance we substract another one
        if (lval == -rval) result = ll();
        else if (lval.abs() >= rval.abs())
        {
            for (int i = 0; i < minsize; i++)
            {
                sub = power::mod * static_cast<long long>(lval.num[i] < rval.num[i] + sub) + lval.num[i] - rval.num[i] - sub;
                result.num.push_back(sub);
                //check for borrowing 1 from higher rank
                sub = ((lval.num[i] < rval.num[i] + sub) ? 1 : 0);
            }
        }
        else 
        {
            for (int i = 0; i < minsize; i++) 
            {
                sub = power::mod * static_cast<long long>(rval.num[i] < lval.num[i] + sub) + rval.num[i] - lval.num[i] - sub;
                result.num.push_back(sub);
                //check for borrowing 1 from higher rank
                sub = (rval.num[i] < lval.num[i] + sub) ? 1 : 0;
            }
            //addition of remainding larger vector's elemenets, which weren't involved in addition, and if necessary we borrow 1 form higher ranks
        }
        if (lval.abs() >= rval.abs())
        {
            for (int i = minsize; i < maxsize; i++) 
            {
                sub = power::mod * (lval.num[i] < sub) + lval.num[i] - sub;
                if (sub > lval.num[i]) sub = 1;
                result.num.push_back(sub);
            }
        }
        else 
        {
            for (int i = minsize; i < maxsize; i++) 
            {
                sub = power::mod * (rval.num[i] < sub) + rval.num[i] - sub;
                if (sub > rval.num[i]) sub = 1;
                result.num.push_back(sub);
            }
        }
        //deleting insignificant 0 from end of vector
        if (result.num.size() > 1 && result.num[result.num.size() - 1] == 0) result.num.pop_back();
        result.sign = ((lval.abs() >= rval.abs()) ? lval.sign : rval.sign);
    }
    flush(result.num);
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
    return ll(lval.sign ^ rval.sign, ansy);
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
        while(to[i] == static_cast<char>(39)) to.erase(i, 1);
        digit = digit + (static_cast<long long>(to[i]) - 48) * degree;
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
        if(!(i == n - 1 && val.num[i] < 2)) new_val.push_back(val.num[i] / 2);
        if(i) new_val[i - 1] = new_val[i - 1] + val.num[i] % 2 * (power::mod / 2);
        //std::cout << new_val[i] << std::endl;
    }
    flush(new_val);
    return ll(val.sign, new_val);
}

ll operator /(const ll& lval, const ll& rval)
{
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
    return l;
}

ll operator %(const ll& lval, const ll& rval) { return lval - lval / rval * rval;  }
//The repair is over

template <class Type>
Type gcd(Type a, Type b)
{
    while(a!=0 && b!=0){
        Type tmp = a;
        a = b;
        b = tmp%b;
    }
    if(a>b) return a;
    return b;
}

template <class Type>
Type lcm(Type a, Type b)
{
    return a / gcd(a, b) * b;
}

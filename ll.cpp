#include "ll.h"

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
/**\brief îïåðàòîð < äëÿ äâóõ ll ÷èñåë
 * Ñðàâíèâàåò ïîñëåäîâàòåëüíî ñíà÷àëà çíàêè ÷èñåë, ïîòîì èõ äëèíó, ïîòîì íà÷èíàÿ ñ íàèáîëüøåãî ñðàâíèâàåò èõ ïîñèìâîëüíî
 * Çàâèñèò îò îïåðàòîðîâ > è !=
 * Àñèìïòîòèêà ïî âðåìåíè - O(n), êîíñòàíòà àñèìïòîòèêè 2
 * Àñèìïòîòèêà ïî ïàìÿòè - O(1), êîíñòàíòà àñèìïòîòèêè 2
 * \param lval const ll& ëåâîå ÷èñëî
 * \param rval const ll& ïðàâîå ÷èñëî
 * \return bool true, åñëè ëåâîå ìåíüøå ïðàâîãî, èíà÷å false
 */
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

template<typename T> //îáúÿâëåíèå ïàðàìåòðà øàáëîíà ôóíêöèè
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
=======
#include "ll.h"

namespace power{
    const int mod = 1000000000;
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

#pragma once
#include "rational.h"

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
    polinom<IND, COEF>(COEF n)
    {
        if (n >= 0.0001 || n <= -0.0001)
        {
            ind.push_back(0);
            coef[0] = n;
        }
    }
    polinom<IND, COEF>(IND l, COEF n)
    {
        if (n >= 0.0001 || n <= -0.0001)
        {
            ind.push_back(l);
            coef[l] = n;
        }
    }
    polinom<IND, COEF>(std::vector<COEF> Coef)
    {
        for (int i = 0, n = Coef.size(); i < n; i++)
        {
            if (Coef[i] >= 0.001 || Coef[i] <= -0.001)
            {
                ind.push_back(IND(i));
                coef[IND(i)] = Coef[i];
            }
        }
    }
    polinom<IND, COEF>(std::vector<IND> Ind, std::map<IND, COEF> Coef) : ind(Ind), coef(Coef) {}
    polinom<IND, COEF>(std::vector<IND> Ind, std::vector<COEF> Coef) : ind(Ind) { for (int i = 0, n = Ind.size(); i < n; i++) coef[ind[i]] = Coef[i]; }
    polinom<IND, COEF>(std::string pol)
    {
        std::string polres = "";
        pol = "#" + pol;
        bool k = 0, upkey = 0;
        for (int i = 0; pol[i]; i++, k = 0)
        {
            while (pol[i] && (pol[i] == ' ' || pol[i] == '*' || pol[i] == ')' || pol[i] == '(')) pol.erase(i, 1);
            if (pol[i] == 'x')
            {
                if (pol[i - 1] < '0' || pol[i - 1] > '9') polres = polres + '1';
                if (pol[i + 1] != '^') k = 1;
            }
            polres = polres + pol[i];
            if (k) polres = polres + "^1";
        }
        for (int i = 0, n = polres.size(); i < n; i++)
        {
            if (polres[i] >= '0' && polres[i] <= '9' && polres[i - 1] != '^' && (polres[i - 1] < '0' || polres[i - 1] > '9'))
            {
                while (i < n && polres[i] >= '0' && polres[i] <= '9') i++;
                if (i == n || polres[i] != 'x') polres.insert(i, "x^0");
            }
        }
        polres = polres + '+';
        polres.erase(0, 1);
        //std::cout << polres << '\n';
        std::string num;
        COEF Coef;
        IND Ind;
        for (int i = 0, n = polres.size(); i < n; i++)
        {
            if (polres[i] == 'x')
            {
                std::istringstream in(num);
                in >> Coef;
                num = "";
                i += 2;
            }
            else if (i && polres[i] == '-' || polres[i] == '+')
            {
                std::istringstream in(num);
                in >> Ind;
                if (Coef < -0.0001 || 0.0001 < Coef)
                {
                    ind.push_back(IND(Ind));
                    coef[Ind] = COEF(Coef);
                }
                num = "";
                if (polres[i] == '+') i++;
            }
            if (i < n) num = num + polres[i];
        }
        std::sort(ind.begin(), ind.end());
    }

    template <class IND, class COEF> friend bool operator ==(const polinom<IND, COEF>&, const polinom<IND, COEF>&);
    template <class IND, class COEF, class type> friend bool operator ==(const polinom<IND, COEF>& l_val, const type& r_val) { return (l_val == polinom<IND, COEF>(r_val)); }
    template <class IND, class COEF, class type> friend bool operator ==(const type& l_val, const polinom<IND, COEF>& r_val) { return (r_val == l_val); }

    template <class IND, class COEF> friend bool operator !=(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val) { return (!(l_val == r_val)); }
    template <class IND, class COEF, class type> friend bool operator !=(const polinom<IND, COEF>& l_val, const type& r_val) { return (l_val != polinom<IND, COEF>(r_val)); }
    template <class IND, class COEF, class type> friend bool operator !=(const type& l_val, const polinom<IND, COEF>& r_val) { return (r_val != l_val); }

    template <class IND, class COEF> friend polinom<IND, COEF> operator -(const polinom<IND, COEF>&);
    template <class IND, class COEF> friend polinom<IND, COEF> operator +(const polinom<IND, COEF>&, const polinom<IND, COEF>&);
    template <class IND, class COEF> friend polinom<IND, COEF> operator -(const polinom<IND, COEF>&, const polinom<IND, COEF>&);
    template <class IND, class COEF> friend polinom<IND, COEF> operator *(const polinom<IND, COEF>&, const polinom<IND, COEF>&);
    template <class IND, class COEF> friend polinom<IND, COEF> operator /(const polinom<IND, COEF>&, const polinom<IND, COEF>&);
    template <class IND, class COEF> friend polinom<IND, COEF> operator %(const polinom<IND, COEF>&, const polinom<IND, COEF>&);
    /*std::ostream& operator>> (std::ostream& out, const polinom& val);
    vector< complex<T> > roots();
    friend polinom gcd(polinom l_val, polinom r_val);*/
    template <class IND, class COEF> friend COEF substitution(polinom<IND, COEF>& val, COEF& x);
    template <class IND, class COEF> friend COEF integral(polinom<IND, COEF>& pol, COEF& l_val, COEF& r_val);
    template <class IND, class COEF> friend polinom<IND, COEF> derivative(polinom<IND, COEF>& val);
    template <class IND, class COEF> friend polinom<IND, COEF> integral(polinom<IND, COEF>& val, COEF& C);
    template <class IND, class COEF> friend std::ostream& operator<< (std::ostream&, const polinom<IND, COEF>&);
};

template <class IND, class COEF>
bool operator ==(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
    polinom<IND, COEF> lv = l_val,
        rv = r_val;
    int n = l_val.ind.size();
    if (n != r_val.ind.size()) return false;
    for (int i = 0; i < n; i++)
    {
        if (l_val.ind[i] != r_val.ind[i]) return false;
        if (lv.coef[l_val.ind[i]] != rv.coef[r_val.ind[i]]) return false;
    }
    return true;
}

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
polinom<IND, COEF> operator -(const polinom<IND, COEF>& val)
{
    polinom<IND, COEF> value = val;
    std::map<IND, COEF> new_coef;
    for (const COEF& to : val.ind) new_coef[to] = -value.coef[to];
    return polinom<IND, COEF>(val.ind, new_coef);
}

// вычитание полиномов
template <typename IND, typename COEF>
polinom<IND, COEF> operator -(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
    polinom<IND, COEF> lv = l_val,
        rv = r_val;
    std::vector<IND> new_ind = merge(lv.ind, rv.ind);
    std::map<IND, COEF> new_coef;
    for (const IND& to : new_ind) new_coef[to] = lv.coef[to] - rv.coef[to];
    int l = 0;
    for (const IND& to : new_ind) if (new_coef[to] != 0) new_ind[l++] = to;
    new_ind.resize(l);
    return polinom<IND, COEF>(new_ind, new_coef);
}

// сложение многочленов
template <typename IND, typename COEF>
polinom<IND, COEF> operator +(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
    polinom<IND, COEF> lv = l_val,
        rv = r_val;
    std::vector<IND> new_ind = merge(lv.ind, rv.ind);
    std::map<IND, COEF> new_coef;
    for (const IND& to : new_ind) new_coef[to] = lv.coef[to] + rv.coef[to];
    int l = 0;
    for (const IND& to : new_ind) if (new_coef[to] != 0) new_ind[l++] = to;
    new_ind.resize(l);
    return polinom<IND, COEF>(new_ind, new_coef);
}

// оператор вывода
template <typename IND, typename COEF>
std::ostream& operator<< (std::ostream& out, const polinom<IND, COEF>& val)
{
    polinom<IND, COEF> value = val;
    int n = value.ind.size();
    if (n == 0) out << 0;
    else for (int i = 0; i < n; i++)
    {
        IND to = value.ind[n - i - 1];
        if (i && value.coef[to] > 0) out << "+";
        if (value.coef[to] == -1) out << '-';
        else if (to == 0 || !(value.coef[to] <= 1.0001 && value.coef[to] >= 0.9999)) out << value.coef[to];
        if (to > 0) out << 'x';
        if (to > 1)
        {
            out << "^" << to;
            if (i < n - 1) out << ' ';
        }
    }
    return out;
}

template<class IND, class COEF>
std::istream& operator>> (std::istream& in, polinom<IND, COEF>& val)
{
    std::string value;
    getline(in, value);
    val = polinom<IND, COEF>(value);
    return in;
}
// умножение полиномов
template <typename IND, typename COEF>
polinom<IND, COEF> operator *(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
    polinom<IND, COEF> lv = l_val,
        rv = r_val;
    if (l_val == 0 || r_val == 0) return polinom<IND, COEF>();
    IND comp = std::max(l_val.ind[l_val.ind.size() - 1], r_val.ind[r_val.ind.size() - 1]);
    /* умножение полиномов степени большей чем 1000000. Стандартное умножение "в столбик"*/
    if (1 || comp * sizeof(COEF) > static_cast<long long>(1 << 30))
    {
        std::vector<IND> new_ind;
        std::map<IND, COEF> new_coef;
        for (const IND& l : l_val.ind)
        {
            for (const IND& r : r_val.ind)
            {
                //std::cout << l << ' ' << r << '\n';
                new_coef[l + r] = new_coef[l + r] + lv.coef[l] * rv.coef[r];
                new_ind.push_back(l + r);
            }
        }
        std::sort(new_ind.begin(), new_ind.end());
        int l = 1, n = new_ind.size();
        for (int i = 1; i < n; i++) if (new_ind[i] != new_ind[i - 1] && new_coef[new_ind[i]] != 0) new_ind[l++] = new_ind[i];
        new_ind.resize(l);
        return polinom<IND, COEF>(new_ind, new_coef);
    }
}

// деление полиномов
//реализовано через умножение
template <typename IND, typename COEF>
polinom<IND, COEF> operator /(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
    //std::cout << "\n\n\n";
    assert(r_val != 0);
    polinom<IND, COEF> rv = r_val;
    std::vector<IND> new_ind;
    std::map<IND, COEF> new_coef;
    if (r_val.ind[r_val.ind.size() - 1] > l_val.ind[l_val.ind.size() - 1]) return polinom<IND, COEF>(new_ind, new_coef);
    polinom<IND, COEF> div(l_val);
    IND r = r_val.ind[r_val.ind.size() - 1], l = div.ind[div.ind.size() - 1];
    while (r <= l)
    {
        //std::cout << l << ' ' << r << ' ' << (l - r) << std::endl;
        new_ind.push_back(l - r);
        new_coef[l - r] = div.coef[l] / rv.coef[r];
        //std::cout << new_coef[l - r] << std::endl;
        polinom<IND, COEF> g(l - r, new_coef[l - r]);
        //std::cout << g << std::endl;
        g = g * rv;
        //std::cout << g << std::endl;
        div = div - g;
        //std::cout << l << std::endl;
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
polinom<IND, COEF> operator %(const polinom<IND, COEF>& l_val, const polinom<IND, COEF>& r_val)
{
    polinom<IND, COEF> ans = l_val, help = l_val / r_val;
    help = help * r_val;
    ans = l_val - help;
    return ans;
}
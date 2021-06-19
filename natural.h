/**\file vln.h
 * \brief Cодержит в себе класс целых чисел \ref vln "класс длинных натуральных"
 * \authors Андрей, Артём и Владислав
*/
#pragma once
#include "ll.h"
/** \class vln
 *  \brief Класс очень длинных натуральных чисел
 *	\details Реализует в себе все необходимо-достаточные возможности для работы с очень длинным натуральными числами, такие как сравнение, и простейщие арифметические операции, а так же вывод их в стандартные потоки\n
 *  Само длинное число представлено в ввиде массива его цифр, сгруппированных по 9
 *  \authors Андрей, Артём и Владислав
 */
class vln
{
private:
    ll num;

public:
    //Пинаев Артём 0306
    vln() : num{ 0 } {}
    vln(const ll& to) : num(to) {}
    vln(int to) : num{ ll(to) } {}
    vln(long long to) : num{ ll(to) } {}
    vln(std::string to) : num{ ll(to) } {}
    vln(std::vector<long long> nuM) : num{ ll(false, nuM) } {}
    friend std::ostream& operator<< (std::ostream& out, const vln& val);
    
    ll getNum() { return num; }

    //Новиков Владислав 0306
    friend bool operator ==(const vln& lval, const vln& rval) { return (lval.num == rval.num); }
    template <typename T> friend bool operator ==(const vln& lval, const T& rval) { return (lval == vln(rval)); }
    template <typename T> friend bool operator ==(const T& lval, const vln& rval) { return (vln(lval) == rval); }

    friend bool operator < (const vln& lval, const vln& rval) { return (rval.num > lval.num); }
    template <typename T> friend bool operator < (const vln& lval, const T& rval) { return (lval < vln(rval)); }
    template <typename T> friend bool operator < (const T& lval, const vln& rval) { return (vln(lval) < rval); }

    friend bool operator > (const vln& lval, const vln& rval) { return (lval.num > rval.num); }
    template <typename T> friend bool operator > (const vln& lval, const T& rval) { return (lval > vln(rval)); }
    template <typename T> friend bool operator > (const T& lval, const vln& rval) { return (vln(lval) > rval); }

    friend bool operator !=(const vln& lval, const vln& rval) { return (lval.num != rval.num); }
    template <typename T> friend bool operator !=(const vln& lval, const T& rval) { return (lval != vln(rval)); }
    template <typename T> friend bool operator !=(const T& lval, const vln& rval) { return (vln(lval) != rval); }

    friend bool operator >=(const vln& lval, const vln& rval) { return (lval.num >= rval.num); }
    template <typename T> friend bool operator >=(const vln& lval, const T& rval) { return (lval >= vln(rval)); }
    template <typename T> friend bool operator >=(const T& lval, const vln& rval) { return (vln(lval) >= rval); }

    friend bool operator <=(const vln& lval, const vln& rval) { return (lval.num <= rval.num); }
    template <typename T> friend bool operator <=(const vln& lval, const T& rval) { return (lval <= vln(rval)); }
    template <typename T> friend bool operator <=(const T& lval, const vln& rval) { return (vln(lval) <= rval); }

    //Пинаев Артём 0306
    friend vln operator +(const vln& lval, const vln& rval) { return vln(ll(lval) + ll(rval)); }       //N4
    template <typename T> friend vln operator +(const vln& lval, const T& rval) { return (lval + vln(rval)); }
    template <typename T> friend vln operator +(const T& lval, const vln& rval) { return (vln(lval) + rval); }

    friend vln operator -(const vln& lval, const vln& rval) { assert(lval >= rval); return vln(ll(lval) - ll(rval)); }       //N5
    template <typename T> friend vln operator -(const vln& lval, const T& rval) { return (lval - vln(rval)); }
    template <typename T> friend vln operator -(const T& lval, const vln& rval) { return (vln(lval) - rval); }

    //Андрей Комраков
    friend vln operator *(const vln& lval, const vln& rval) { return vln(ll(lval) * ll(rval)); }       //N8
    template <typename T> friend vln operator *(const vln& lval, const T& rval) { return (lval * vln(rval)); }
    template <typename T> friend vln operator *(const T& lval, const vln& rval) { return (vln(lval) * rval); }

    friend vln operator /(const vln& lval, const vln& rval) { return vln(ll(lval) / ll(rval)); }       //N12
    template <typename T> friend vln operator /(const vln& lval, const T& rval) { return (lval / vln(rval)); }
    template <typename T> friend vln operator /(const T& lval, const vln& rval) { return (vln(lval) / rval); }

    friend vln operator %(const vln& lval, const vln& rval) { return vln(ll(lval) % ll(rval)); }       //N11
    template <typename T> friend vln operator %(const vln& lval, const T& rval) { return (lval % vln(rval)); }
    template <typename T> friend vln operator %(const T& lval, const vln& rval) { return (vln(lval) % rval); }

    char com(const vln& secval); //N1
    bool nzer();                 //N2
    vln inc();                   //N3
    vln mulk(long long k);       //N7
    vln sub(long long k, const vln& secval); //N9
    vln div(const vln& secval);  //*N10
    friend std::istream& operator>> (std::istream& in, vln& val);
};

ll::ll(vln val) { (*this) = val.getNum(); }

//Новиков Владислав 0306
/** \brief Сравнение 2 чисел
 * \details Сравнение натуральных чисел: 2 - если первое больше второго, 0, если равно, 1 иначе.
 * \param secval const vln& второе число, с которым происходит сравнение
 * \return char 2 - если первое больше второго, 0, если равно, иначе 1
 * \authors Владислав
 */
char vln::com(const vln& secval)
{
    if (num > secval.num) return 2;
    if (num == secval.num) return 0;
    return 1;
}

/** \brief Равенство нулю
 * \details Проверка на ноль: если число не равно нулю, то «да» иначе «нет»
 * \authors Владислав
 * \return bool true если оно равно нулю, false если не равно
 */
bool vln::nzer() { return num == 0; }

//Пинаев Артём 0306
/** \brief Инкремент
 * \details Добавление 1 к натуральному числу
 * \authors Артём
 * \return vln полученное число
 */
vln vln::inc()
{
    num = num + 1;
    return (*this);
};                   //N3

/** \brief Умножает на 10^k
 * \details Умножение натурального числа на 10^k
 * \param k степень 10
 * \authors Андрей
 * \return vln полученное число
 */
vln vln::mulk(long long k)       //N7
{
    for (long long i = 0; i < k; i++)
        *this = *this * 10;
    return *this;
}

/** \brief Делит на число, умноженное на k
 * \details Вычитание из натурального другого натурального, умноженного на цифру для случая с неотрицательным результатом
 * \param k long long - множитель натурального
 * \param secval const vln& - длинное натуральное число
 * \return vln разность между нашим числом и secval*k
 * \authors Андрей
 */
vln vln::sub(long long k, const vln& secval) { return ((*this) - (secval * k)); }

/** \brief Старшая цифра деления двух чисел
 * \details Вычисление первой цифры деления большего натурального на меньшее, домноженное на 10^k,где k - номер позиции этой цифры (номер считается с нуля)
 * \authors Андрей
 * \param secval const vln& делитель
 * \return vln первая цифра деления домноженная на 10^k,
 */
vln vln::div(const vln& secval)
{
    (*this) = (*this) / secval;
    vln temp = (*this);
    vln k = 1;
    while ((*this) > 9)
    {
        temp = temp / 10;
        k = k * 10;
    }
    return ((*this) % k);
}  //*N10

/** \brief Вывод в поток
 * \details Выводит указанное длинное натуральное число в указанный поток
 * \authors Артём
 * \param out std::ostream& поток для вывода
 * \param secval const vln& выводимое число
 * \return std::ostream& поток с чис лом в нём
 */
std::ostream& operator<< (std::ostream& out, const vln& val)
{
    out << val.num;
    return out;
}
std::istream& operator>> (std::istream& in, vln& val)
{
    in >> val.num;
    return in;
}

std::string toString(vln val)
{
    std::ostringstream string;
    string << val;
    return string.str();
}

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

#include "ll.h"

/**\brief �������� > ��� ���� ll �����
 * ���������� ��������������� ������� ����� �����, ����� �� �����, ����� ������� � ����������� ���������� �� �����������
 * �� ������� �� ������ ������� � ����������
 * ����������� �� ������� - O(n), ��������� ����������� 2
 * ����������� �� ������ - O(1), ��������� ����������� 2
 * \param lval const ll& ����� �����
 * \param rval const ll& ������ �����
 * \return bool true, ���� ����� ������ �������, ����� false
 */
bool operator >(const ll& lval, const ll& rval)
{   if (lval.sign!=rval.sign)
        return lval.sign<rval.sign;
    auto lsize=lval.num.size();
    if (lsize!=rval.num.size())
        return ((lsize>rval.num.size())^lval.sign);
    for (int i=0; i<lsize; i++)
        if (lval.num[i]!=rval.num[i])
            return (lval.num[i]>rval.num[i])^lval.sign;
    return 0;
}
/**\brief �������� < ��� ���� ll �����
 * ���������� ��������������� ������� ����� �����, ����� �� �����, ����� ������� � ����������� ���������� �� �����������
 * ������� �� ���������� > � !=
 * ����������� �� ������� - O(n), ��������� ����������� 2
 * ����������� �� ������ - O(1), ��������� ����������� 4
 * \param lval const ll& ����� �����
 * \param rval const ll& ������ �����
 * \return bool true, ���� ����� ������ �������, ����� false
 */
 bool operator < (const ll& lval, const ll& rval)
{   return (!(lval>rval) && lval!=rval);
}

template<typename T>
bool operator >(const T& lval, const ll& rval)
{   ll lv(lval);
    return lv>rval;
}

template<typename T>
bool operator >(const ll& lval, const ll& rval)
{   ll rv(rval);
    return lval>rv;
}

template<typename T>
bool operator <(const T& lval, const ll& rval)
{   ll lv(lval);
    return lv<rval;
}

template<typename T>
bool operator <(const ll& lval, const T& rval)
{   ll rv(rval);
    return lval<rv;
}

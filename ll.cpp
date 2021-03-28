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
 * ����������� �� ������ - O(1), ��������� ����������� 2
 * \param lval const ll& ����� �����
 * \param rval const ll& ������ �����
 * \return bool true, ���� ����� ������ �������, ����� false
 */
 bool operator < (const ll& lval, const ll& rval)
{   return rval>lval;
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

bool operator ==(const ll &lval, const ll &rval){
    if (lval.sign != rval.sign){
        return false;// �� �����
    else{
        unsigned int len1 = lval.num.size();
        if (len1 != rval.num.size()) return false; // �� �����
        else
            for (unsigned int i = 0; i<len1; i++)
                if (lval.num[i] != rval.num[i])
                    return false;
            return true;
    }
}

bool operator !=(const ll& lval, const ll& rval){
    return !(lval == rval);
}

template<typename T> //���������� ��������� ������� �������
T operator >= (const T& lval, const ll& rval)
{   return !(lval>rval);
}

template<typename T>
T operator >= (const T& lval, const ll& rval)
{   return !(lval<rval);
}

template<typename T>
T operator <= (const T& lval, const ll& rval)
{   return !(lval>rval);
}

template<typename T>
T operator <= (const T& lval, const ll& rval)
{   return !(lval>rval);
}

short ll::poz()
{   if (this->num[0] == 0) return 0;
    else if (this->sign) return 1;
    else if (!this->sign) return 2;
}

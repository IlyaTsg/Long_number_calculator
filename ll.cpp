#include "ll.h"

/**\brief �������� > ��� ���� ll �����
 * ���������� ��������������� ������� ����� �����, ����� �� �����, ����� ������� � ����������� ���������� �� �����������
 * �� ������� �� ������ ������� � ����������
 * ����������� �� ������� - O(n), ��������� ����������� 2
 * ����������� �� ������ - O(1), ��������� ����������� 3
 * \param lval const ll& ����� �����
 * \param rval const ll& ������ �����
 * \return bool true, ���� ����� ������ �������, ����� false
 */
bool operator >(const ll& lval, const ll& rval)
{   if (lval.sign!=rval.sign)
        return lval.sign<rval.sign;
    auto lsize=lval.num.size();
    auto rsize=rval.num.size();
    if (lsize!=rsize)
        return ((lsize>rsize)^lval.sign);
    for (int i=0; i<lsize; i++)
        if (lval.num[i]!=rval.num[i])
            return (lval.num[i]>rval.num[i])^lval.sign;
    return 0;
}
/**\brief �������� < ��� ���� ll �����
 * ���������� ��������������� ������� ����� �����, ����� �� �����, ����� ������� � ����������� ���������� �� �����������
 * ������� �� ���������� > � !=
 * ����������� �� ������� - O(n), ��������� ����������� 2
 * ����������� �� ������ - O(1), ��������� ����������� 3
 * \param lval const ll& ����� �����
 * \param rval const ll& ������ �����
 * \return bool true, ���� ����� ������ �������, ����� false
 */bool operator < (const ll& lval, const ll& rval)
{   return (!(lval>rval) && lval!=rval);
}

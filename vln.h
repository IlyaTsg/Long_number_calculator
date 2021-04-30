/**\file vln.h
 * \brief C������� � ���� ����� ����� ����� \ref vln "����� ������� �����������"
 * \authors ������, ���� � ���������
*/
#pragma once
#include "ll.h"
/** \class vln
 *  \brief ����� ����� ������� ����������� �����
 *	\details ��������� � ���� ��� ����������-����������� ����������� ��� ������ � ����� ������� ������������ �������, ����� ��� ���������, � ���������� �������������� ��������, � ��� �� ����� �� � ����������� ������\n
 *  ���� ������� ����� ������������ � ����� ������� ��� ����, ��������������� �� 9
 *  \authors ������, ���� � ���������
 */
class vln
{
private:
    ll num;

public:
//������ ���� 0306
    vln(): num{ 0 }{}
    vln(int to): num{ ll(to) }{}
    vln(long long to): num{ ll(to) }{}
    vln(std::string to): num{ ll(to) }{}
    vln(std::vector<long long> nuM): num{ ll(false, nuM) }{}
    friend std::ostream& operator<< (std::ostream& out, const vln& val);
//������� ��������� 0306
    friend bool operator ==(const vln &lval, const vln &rval) { return (lval.num == rval.num); }
    template <typename T> friend bool operator ==(const vln& lval, const T&  rval) { return (lval == vln(rval)); }
    template <typename T> friend bool operator ==(const T&  lval, const vln& rval) { return (vln(lval) == rval); }
    friend bool operator < (const vln& lval, const vln& rval) { return (rval.num > lval.num); }
    template <typename T> friend bool operator < (const vln& lval, const T&  rval) { return (lval < vln(rval)); }
    template <typename T> friend bool operator < (const T&  lval, const vln& rval) { return (vln(lval) < rval); }
    friend bool operator > (const vln& lval, const vln& rval) { return (lval.num > rval.num); }
    template <typename T> friend bool operator > (const vln& lval, const T&  rval) { return (lval > vln(rval)); }
    template <typename T> friend bool operator > (const T&  lval, const vln& rval) { return (vln(lval) > rval); }
    friend bool operator !=(const vln& lval, const vln& rval) { return (lval.num != rval.num); }
    template <typename T> friend bool operator !=(const vln& lval, const T&  rval) { return (lval != vln(rval)); }
    template <typename T> friend bool operator !=(const T&  lval, const vln& rval) { return (vln(lval) != rval); }
    friend bool operator >=(const vln& lval, const vln& rval) { return (lval.num >= rval.num); }
    template <typename T> friend bool operator >=(const vln& lval, const T&  rval) { return (lval >= vln(rval)); }
    template <typename T> friend bool operator >=(const T&  lval, const vln& rval) { return (vln(lval) >= rval); }
    friend bool operator <=(const vln& lval, const vln& rval) { return (lval.num <= rval.num); }
    template <typename T> friend bool operator <=(const vln& lval, const T&  rval) { return (lval <= vln(rval)); }
    template <typename T> friend bool operator <=(const T&  lval, const vln& rval) { return (vln(lval) <= rval); }
//������ ���� 0306
    friend vln operator +(const vln& lval, const vln& rval);       //N4
    template <typename T> friend vln operator +(const vln& lval, const T&  rval) { return (lval + vln(rval)); }
    template <typename T> friend vln operator +(const T&  lval, const vln& rval) { return (vln(lval) + rval); }
    friend vln operator -(const vln& lval, const vln& rval);       //N5
    template <typename T> friend vln operator -(const vln& lval, const T&  rval) { return (lval - vln(rval)); }
    template <typename T> friend vln operator -(const T&  lval, const vln& rval) { return (vln(lval) - rval); }
//������ ��������
    friend vln operator *(const vln& lval, const vln& rval);       //N8
    template <typename T> friend vln operator *(const vln& lval, const T&  rval) { return (lval * vln(rval)); }
    template <typename T> friend vln operator *(const T&  lval, const vln& rval) { return (vln(lval) * rval); }
    friend vln operator /(const vln& lval, const vln& rval);       //N12
    template <typename T> friend vln operator /(const vln& lval, const T&  rval) { return (lval / vln(rval)); }
    template <typename T> friend vln operator /(const T&  lval, const vln& rval) { return (vln(lval) / rval); }
    friend vln operator %(const vln& lval, const vln& rval);       //N11
    template <typename T> friend vln operator %(const vln& lval, const T&  rval) { return (lval % vln(rval)); }
    template <typename T> friend vln operator %(const T&  lval, const vln& rval) { return (vln(lval) % rval); }

    char com(const vln& secval); //N1
    bool nzer();                 //N2
    vln inc();                   //N3
    vln mulk(long long k);       //N7
    vln sub(long long k, const vln& secval); //N9
    vln div(const vln& secval);  //*N10
};

//������� ��������� 0306
/** \brief ��������� 2 �����
 * \details ��������� ����������� �����: 2 - ���� ������ ������ �������, 0, ���� �����, 1 �����.
 * \param secval const vln& ������ �����, � ������� ���������� ���������
 * \return char 2 - ���� ������ ������ �������, 0, ���� �����, ����� 1
 * \authors ���������
 */
char vln::com(const vln& secval)
{
    if (this->num > secval.num) return 2;
    else if (this->num == secval.num) return 0;
    else return 1;
}

/** \brief ��������� ����
 * \details �������� �� ����: ���� ����� �� ����� ����, �� ��� ����� ����
 * \authors ���������
 * \return bool true ���� ��� ����� ����, false ���� �� �����
 */
bool vln::nzer() { return num == 0; }

//������ ���� 0306
/** \brief ���������
 * \details ���������� 1 � ������������ �����
 * \authors ����
 * \return vln ���������� �����
 */
vln vln::inc(){
    this->num = this->num + 1;
    return *this;
};                   //N3

/** \brief �������� �� 10^k
 * \details ��������� ������������ ����� �� 10^k
 * \param k ������� 10
 * \authors ������
 * \return vln ���������� �����
 */
vln vln::mulk(long long k)       //N7
{   for (long long i=0; i<k; i++)
        *this=*this*10;
    return *this;
}

/** \brief ����� �� �����, ���������� �� k
 * \details ��������� �� ������������ ������� ������������, ����������� �� ����� ��� ������ � ��������������� �����������
 * \param k long long - ��������� ������������
 * \param secval const vln& - ������� ����������� �����
 * \return vln �������� ����� ����� ������ � secval*k
 * \authors ������
 */
vln vln::sub(long long k, const vln& secval) { return (this-(secval*k)); }

/** \brief ������� ����� ������� ���� �����
 * \details ���������� ������ ����� ������� �������� ������������ �� �������, ����������� �� 10^k,��� k - ����� ������� ���� ����� (����� ��������� � ����)
 * \authors ������
 * \param secval const vln& ��������
 * \return vln ������ ����� ������� ����������� �� 10^k,
 */
vln vln::div(const vln& secval)
{   *this=*this/secval;
    vln temp=*this;
    vln k=0;
    while(*this>9)
    {   temp=temp/10;
        k=k*10;
    }
    return (*this%k);
}  //*N10

/** \brief ����� � �����
 * \details ������� ��������� ������� ����������� ����� � ��������� �����
 * \authors ����
 * \param out std::ostream& ����� ��� ������
 * \param secval const vln& ��������� �����
 * \return std::ostream& ����� � ������ � ��
 */
std::ostream& operator<< (std::ostream& out, const vln& val) {
	out << val.num;
	return out;
}

#include "vln.h"
#include <iostream>

//Пинаев Артём 0306
vln::vln(): num{ 0 }{};

vln::vln(int to){
    ll(to);
};

vln::vln(long long to){
    ll(to);
};

vln::vln(std::string to){
    ll(to);
};

vln::vln(std::vector<long long> nuM){
    ll(nuM);
};
//Новиков Владислав 0306
bool operator ==(const vln &lval, const vln &rval)
{
    return lval.num == rval.num;
}

template <typename T>
bool operator ==(const vln& lval, const T&  rval)
{
    return lval.num == rval.num;
}

template <typename T>
bool operator ==(const T&  lval, const vln& rval)
{
    return lval.num == rval.num;
}

bool operator < (const vln& lval, const vln& rval)
{
    return lval.num < rval.num;
}

template <typename T>
bool operator < (const vln& lval, const T&  rval)
{
    return lval.num < rval.num;
}

template <typename T>
bool operator < (const T&  lval, const vln& rval)
{
    return lval.num < rval.num;
}

bool operator > (const vln& lval, const vln& rval)
{
    return lval.num > rval.num;
}

template <typename T>
bool operator > (const vln& lval, const T&  rval)
{
    return lval.num > rval.num;
}

template <typename T>
bool operator > (const T&  lval, const vln& rval)
{
    return lval.num > rval.num;
}

bool operator !=(const vln& lval, const vln& rval)
{
    return lval.num != rval.num;
}

template <typename T>
bool operator !=(const vln& lval, const T&  rval)
{
    return lval.num != rval.num;
}

template <typename T>
bool operator !=(const T&  lval, const vln& rval)
{
    return lval.num != rval.num;
}

bool operator >=(const vln& lval, const vln& rval)
{
    return lval.num >= rval.num;
}

template <typename T>
bool operator >=(const vln& lval, const T&  rval)
{
    return lval.num >= rval.num;
}

template <typename T>
bool operator >=(const T&  lval, const vln& rval)
{
    return lval.num >= rval.num;
}

bool operator <=(const vln& lval, const vln& rval)
{
    return lval.num <= rval.num;
}

template <typename T>
bool operator <=(const vln& lval, const T&  rval)
{
    return lval.num <= rval.num;
}

template <typename T>
bool operator <=(const T&  lval, const vln& rval)
{
    return lval.num <= rval.num;
}

//Пинаев Артём 0306
vln operator +(const vln& lval, const vln& rval){
    vln temp = vln();
    temp.num = lval.num + rval.num;
    return temp;
};       //N4

template <typename T>
vln operator +(const vln& lval, const T&  rval){
    return lval.num + rval.num;
};

template <typename T>
vln operator +(const T&  lval, const vln& rval){
    return lval.num + rval.num;
};

vln operator -(const vln& lval, const vln& rval){
    vln temp = vln();
    temp.num = lval.num - rval.num;
    return temp;
};       //N5

template <typename T>
vln operator -(const vln& lval, const T&  rval){
    return lval.num - rval.num;
};

template <typename T>
vln operator -(const T&  lval, const vln& rval){
    return lval.num - rval.num;
};

//Новиков Владислав 0306
char vln::com(const vln& secval) //N1
{
    if (this->num > secval.num) return 2;
    else if (this->num == secval.num) return 0;
    else return 1;
}

bool vln::nzer()//N2
{
    return num == 0;
}

//Пинаев Артём 0306
vln vln::inc(){
    this->num = this->num + 1;
    return *this;
};                   //N3

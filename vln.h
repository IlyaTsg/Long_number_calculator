#pragma once
#include <string>
#include "ll.h"
class vln
{
private:
    ll num;

public:
    vln();
    vln(int to);
    vln(long long to);
    vln(std::string to);
    vln(std::vector<long long> nuM);
    friend bool operator ==(const vln &lval, const vln &rval);
    template <typename T>
    friend bool operator ==(const vln& lval, const T&  rval);
    template <typename T>
    friend bool operator ==(const T&  lval, const vln& rval);
    friend bool operator < (const vln& lval, const vln& rval);
    template <typename T>
    friend bool operator < (const vln& lval, const T&  rval);
    template <typename T>
    friend bool operator < (const T&  lval, const vln& rval);
    friend bool operator > (const vln& lval, const vln& rval);
    template <typename T>
    friend bool operator > (const vln& lval, const T&  rval);
    template <typename T>
    friend bool operator > (const T&  lval, const vln& rval);
    friend bool operator !=(const vln& lval, const vln& rval);
    template <typename T>
    friend bool operator !=(const vln& lval, const T&  rval);
    template <typename T>
    friend bool operator !=(const T&  lval, const vln& rval);
    friend bool operator >=(const vln& lval, const vln& rval);
    template <typename T>
    friend bool operator >=(const vln& lval, const T&  rval);
    template <typename T>
    friend bool operator >=(const T&  lval, const vln& rval);
    friend bool operator <=(const vln& lval, const vln& rval);
    template <typename T>
    friend bool operator <=(const vln& lval, const T&  rval);
    template <typename T>
    friend bool operator <=(const T&  lval, const vln& rval);
    friend vln operator +(const vln& lval, const vln& rval);       //N4
    template <typename T>
    friend vln operator +(const vln& lval, const T&  rval);
    template <typename T>
    friend vln operator +(const T&  lval, const vln& rval);
    friend vln operator -(const vln& lval, const vln& rval);       //N5
    template <typename T>
    friend vln operator -(const vln& lval, const T&  rval);
    template <typename T>
    friend vln operator -(const T&  lval, const vln& rval);
    friend vln operator *(const vln& lval, const vln& rval);       //N8
    template <typename T>
    friend vln operator *(const vln& lval, const T&  rval);        //N6
    template <typename T>
    friend vln operator *(const T&  lval, const vln& rval);
    friend vln operator /(const vln& lval, const vln& rval);       //N12
    template <typename T>
    friend vln operator /(const vln& lval, const T&  rval);
    template <typename T>
    friend vln operator /(const T&  lval, const vln& rval);
    friend vln operator %(const vln& lval, const vln& rval);       //N11
    template <typename T>
    friend vln operator %(const vln& lval, const T&  rval);
    template <typename T>
    friend vln operator %(const T&  lval, const vln& rval);

    char com(const vln& secval); //N1
    bool nzer();                 //N2
    vln inc();                   //N3
    vln mulk(long long k);       //N7
    vln sub(long long k, const vln& secval); //N9
    vln div(const vln& secval);  //*N10
    vln gcf(const vln& secval);  //*N13
    vln lcm(const vln& secval);  //*N14
};

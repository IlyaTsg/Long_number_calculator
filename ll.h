#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <complex>

namespace power
{
    const int mod = 1'000'000'000;
    const double PI = 3.141592653589793238462643383279;
}

class ll
{
private:
    std::vector<long long> num;  //Âåêòîð öèôð
    bool sign;              //0 - ïëþñ, 1 - ìèíóñ

public:
    ll();
    ll(bool sig, std::vector<long long> nu): sign(sig), num(nu){}
    ll(int to) :num{ to % power::mod, to / power::mod % power::mod }, sign(to < 0){}
    ll(long long to);
    ll(std::string to);
    ll(bool sigN, std::vector<long long> nuM);
    std::vector<long long> getVec(){
        return num;
    };
    bool getSign(){
        return sign;
    };
    ll operator -() const;
    friend bool operator ==(const ll &lval, const ll &rval);
    friend bool operator < (const ll& lval, const ll& rval);
    template <typename T>
    friend bool operator < (const ll& lval, const T&  rval);
    template <typename T>
    friend bool operator < (const T&  lval, const ll& rval);
    friend bool operator > (const ll& lval, const ll& rval);
    template <typename T>
    friend bool operator > (const ll& lval, const T&  rval);
    template <typename T>
    friend bool operator > (const T&  lval, const ll& rval);
    friend bool operator !=(const ll& lval, const ll& rval);
    friend bool operator >=(const ll& lval, const ll& rval);
    friend bool operator <=(const ll& lval, const ll& rval);
    friend ll operator +(const ll& lval, const ll& rval);       //Z-6
    friend ll operator -(const ll& lval, const ll& rval);       //Z-7
    friend ll operator %(const ll& lval, const ll& rval);       //Z-10
    friend ll operator *(const ll& lval, const ll& rval);       //Z-8
    friend ll operator /(const ll& lval, const ll& rval);       //Z-9
    friend std::ostream& operator<< (std::ostream& out, const ll& val);

    ll abs() const;               //Z-1
    short poz();            //Z-2
    ll rsign();             //Z-3
    ll gcd(ll to);          //N-13

    ll fact();              //Ôàêòîðèàë
    //Ïðî÷èå çàäà÷è äëÿ öåëûõ ÷èñåë
};

void fft(std::vector< std::complex<double> > &to, bool invert);
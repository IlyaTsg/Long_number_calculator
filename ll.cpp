#include "ll.h"

namespace power{
    const int mod = 1000000000;
}

ll::ll(): sign{ false }, num{ 0 }{};
ll::ll(int to): sign{ to < 0 }{
    if (sign) to *= -1;
    num.push_back(to % power::mod);
    num.push_back(to / power::mod);
};
ll::ll(long long to): sign{ to < 0 }{
    if (sign) to *= -1;
    num.push_back(to % power::mod);
    to /= power::mod;
    num.push_back(to % power::mod);
    num.push_back(to / power::mod);
};
ll::ll(std::string to){
    std::string tmp_string;
    long long digit;
    int len = to.length();
    sign = (to[0]=='-')? true:false;
    for(int i=18; len>0; i+=18){
        tmp_string = (len > 18)? to.substr(len-18, 18):to.substr(sign, len-sign);
        digit = std::stoll(tmp_string);
        num.push_back(digit % power::mod);
        if(len>18){
            digit /= power::mod;
            num.push_back(digit % power::mod);
        }
        len -= 18;
    }
    num.push_back(digit / power::mod);
};
ll::ll(bool sigN, std::vector<long long> nuM): sign{ sigN }, num{ nuM }{};
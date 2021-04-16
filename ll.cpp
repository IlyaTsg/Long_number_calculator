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
    int digit = 0, degree = 1;
    if(sign=(to[0]=='-')) to.erase(0,1);
    int len = to.length();
    for(int i=len-1; i>=0; i--){
        digit = digit + ((int)to[i]-48)*degree;
        degree *= 10;
        if(!((len-i)%9)||!i){
            num.push_back(digit);
            digit = 0;
            degree = 1;
        }
    }
};
ll::ll(bool sigN, std::vector<long long> nuM): sign{ sigN }, num{ nuM }{};
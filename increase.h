#ifndef INCREASE_H
#define INCREASE_H

#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
typedef vector<int> vi;

extern int fact[];
extern void print_perm(vi);

vi inc_perm2mid(vi perm) {
    vi mid(perm.size()-1, 0);
    for (int i = 0; i < perm.size(); ++i) {
        if (perm[i] == 1) continue;
        int num_smaller = 0;
        for (int j = i+1; j < perm.size(); ++j) {
            if (perm[j] < perm[i]) num_smaller++;
        }
        mid[perm[i]-2] = num_smaller;
    }
    return mid;
}

vi inc_num2mid(int size, int num) {
    vi ret;
    int k;
    for (k = 1; fact[k+1] < num; ++k);
    while (k) {
        int d = num / fact[k];
        ret.push_back(d);
        num -= d * fact[k];
        k--; // k >= 1 because fact[1] = 1
    }
    while (ret.size() < size-1) ret.push_back(0);
    // stores order: a2, a3, ..., an
    std::reverse(ret.begin(), ret.end());
    return ret;
}

int inc_mid2num(vi mid) {
    int ret = 0;
    int k = mid.size();
    for (int i = mid.size()-1; i >= 0; --i, --k)
        ret += mid[i] * fact[k];
    return ret;
}

vi inc_mid_add_mid(vi mid, vi op) {
    int i = 0, full = 2, carry = 0;
    for (; i < mid.size()&&i < op.size(); i++,full++) {
        mid[i] += op[i] + carry;
        carry = mid[i] / full;
        mid[i] %= full;
    }
    if (carry && i < mid.size()) {
        mid[i] += carry;
        carry = mid[i] / full;
        mid[i] %= full;
        full++;
    }
    return mid;
}

vi inc_mid_minus_mid(vi mid, vi op) {
    // first assume minus is << mid
    assert(op.size() < mid.size());
    int borrow = 0;
    int full = 2;
    int i = 0;
    for (; i < mid.size() && i < op.size(); ++i,full++){
        int t = mid[i] - op[i] - borrow;
        if (t < 0) {
            t += full; // borrow from higher bit
            borrow = 1;
        } else {
            borrow = 0;
        }
        mid[i] = t;
    }
    while (borrow && i < mid.size()) {
        mid[i] -= borrow;
        if (mid[i] < 0) {
            mid[i] += full;
            borrow = 1;
            full++;
            i++;
        } else {
            break;
        }
    }
    return mid;
}

vi inc_mid2perm(vi mid) {
    vi perm(mid.size()+1, 0); // 0, 1, ..., mid.size()
    for (int i = perm.size();
        i > 1;
        --i) {
        int pos, num_space;
        pos = perm.size()-1, num_space = 0;
        for (; pos >= 0 && num_space < mid[i-2]; pos--) {
            if (perm[pos] > 0) continue;
            else num_space++;
        }
        while (perm[pos] > 0 && pos > 0) pos--;
        perm[pos] = i;
    }
    for (int i = 0; i < perm.size(); ++i) if (perm[i] == 0) {
        perm[i] = 1;
        break;
    }
    return perm;
}

vi inc_prev_perm(vi init, int prev_num) {
    vi mid = inc_perm2mid(init);
    int num = inc_mid2num(mid);
    num -= prev_num;
    vi prev_num2mid = inc_num2mid(init.size(), num);
    vi prev_perm = inc_mid2perm(prev_num2mid);
    return prev_perm;
}

vi inc_next_perm(vi init) {
    vi mid = inc_perm2mid(init);
    int num = inc_mid2num(mid);
    num++;
    vi next_num2mid = inc_num2mid(init.size(), num);
    vi next_perm = inc_mid2perm(next_num2mid);
    return next_perm;
}

void inc_test() {
    vi init = {8, 3, 9, 6, 4, 7, 5, 2, 1};
    cout << "Inc init perm: ";
    print_perm(init);
    
    vi mid = inc_perm2mid(init);
    cout << "Inc mid: ";
    print_perm(mid);
    
    vi perm = inc_mid2perm(mid);
    cout << "Inc mid to perm: ";
    print_perm(perm);

    int num = 100;
    vi num2mid = inc_num2mid(perm.size(), num);
    cout << "Inc num to mid: 100 ->";
    print_perm(num2mid);

    mid = {7, 2, 6, 4, 2, 3, 2, 1};
    std::reverse(mid.begin(), mid.end());
    cout << "Inc mid:              "; print_perm(mid);
    
    vi add_mid = inc_mid_add_mid(mid, num2mid);
    cout << "Inc mid add mid:";
    print_perm(add_mid);

    vi minus_mid = inc_mid_minus_mid(mid, num2mid);
    cout << "Inc mid minus mid :   ";
    print_perm(minus_mid);

    int prev_num = 2018;
    num2mid = inc_num2mid(perm.size(), prev_num);
    print_perm(num2mid);

    mid = inc_perm2mid(init); //cout << "Inc mid         :"; print_perm(mid);
    num = inc_mid2num(mid); // cout << "Inc init mid2num: " << num << endl;

    num -= prev_num; // cout << "Inc prev_num    : " << num << endl;
    vi prev_num2mid = inc_num2mid(init.size(), num);
    cout << "Inc prev num2mid:"; print_perm(prev_num2mid);

    vi minus = inc_num2mid(init.size(), prev_num);
    assert(prev_num == inc_mid2num(minus));
    cout << "Inc minus       :"; print_perm(minus);

    vi prev_mid = inc_mid_minus_mid(mid, minus);
    cout << "Inc prev mid    :"; print_perm(prev_mid);

    int prev_mid2num = inc_mid2num(prev_mid);
    cout << "Inc prev mid2num: " << prev_mid2num << endl;

    vi prev_perm = inc_mid2perm(prev_num2mid);

    for (int i = 0; i < 10; i++) {
        vi p = inc_prev_perm(init, i);
        cout << "perm num: " << inc_mid2num(inc_perm2mid(p));
        print_perm(p);
    }
    
}

#endif // !INCREASE_H
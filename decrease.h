#ifndef DECREASE_H
#define DECREASE_H

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

vi dec_perm2mid(vi perm) {
    vi mid(perm.size()-1, 0);
    int size = perm.size();
    for (int i = 0; i < perm.size(); ++i) {
        if (perm[i] == 1) continue;
        int num_smaller = 0;
        for (int j = i+1; j < perm.size(); ++j) {
            if (perm[j] < perm[i]) num_smaller++;
        }
        mid[size-perm[i]] = num_smaller;
    }
    return mid;
}

vi dec_num2mid(int size, int num) {
    vi ret;
    // stores order: a_n, a_(n-1), ..., a2
    while (num && size > 0) {
        ret.push_back(num % size);
        num /= size;
        size--;
    }
    return ret;
}

int dec_mid2num(vi mid) {
    int ret = 0;
    int k = 2;
    for (int i = mid.size()-1; i >= 0; --i, ++k) {
        ret *= k;
        ret += mid[i];
    }
    return ret;
}

vi dec_mid_add_mid(vi mid, vi op) {
    int i = 0, full = mid.size()+1, carry = 0;
    for (; i < mid.size() && i < op.size(); i++,full--) {
        mid[i] += op[i] + carry;
        carry = mid[i] / full;
        mid[i] %= full;
    }
    while (carry && i < mid.size()) {
        mid[i] += carry;
        carry = mid[i] / full;
        mid[i] %= full;
        i++, full--;
    }
    return mid;
}

vi dec_mid_minus_mid(vi mid, vi op) {
    // first assume minus is << mid
    assert(op.size() < mid.size());
    int borrow = 0;
    int full = mid.size()+1;
    int i = 0;
    for (; i < mid.size() && i < op.size(); ++i,full--){
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
            i++, full--;
        } else {
            break;
        }
    }
    return mid;
}

vi dec_mid2perm(vi mid) {
    int size = mid.size()+1;
    vi perm(size, 0); // 0, 1, ..., mid.size()
    for (int i = size; i > 1; --i) {
        int pos, num_space;
        pos = perm.size()-1, num_space = 0;
        for (; pos >= 0 && num_space < mid[size-i]; pos--) {
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

// todo
vi dec_prev_perm(vi init, int prev_num) {
    vi mid = dec_perm2mid(init);
    int num = dec_mid2num(mid);
    num -= prev_num;
    vi prev_num2mid = dec_num2mid(init.size(), num);
    vi prev_perm = dec_mid2perm(prev_num2mid);
    return prev_perm;
}

void dec_test() {
    vi init = {8, 3, 9, 6, 4, 7, 5, 2, 1};
    cout << "Dec init perm: ";
    print_perm(init);
    
    vi mid = dec_perm2mid(init);
    cout << "Dec perm to mid: ";
    print_perm(mid);
    
    vi perm = dec_mid2perm(mid);
    cout << "Dec mid to perm: ";
    print_perm(perm);

    int mid2num = dec_mid2num(mid);
    cout << "Dec init mid2num: " << mid2num << endl;
    
    int num = 2018;
    vi num2mid = dec_num2mid(perm.size(), num);   
    vi add_mid = dec_mid_add_mid(mid, num2mid);
    cout << "Dec mid add mid   :   ";
    print_perm(add_mid);

    vi minus_mid = dec_mid_minus_mid(mid, num2mid);
    cout << "Dec mid minus mid :   ";
    print_perm(minus_mid);

    int prev_num = 2018;

    mid2num -= prev_num;
    cout << "Dec prev_num    : " << mid2num << endl;

    vi prev_num2mid = dec_num2mid(init.size(), mid2num);
    cout << "Dec prev num2mid:"; print_perm(prev_num2mid);

    vi minus = dec_num2mid(init.size(), prev_num);
    cout << "Dec minus       :"; print_perm(minus);

    vi prev_mid = dec_mid_minus_mid(mid, minus);
    cout << "Dec prev mid-mid:"; print_perm(prev_mid);

    int prev_mid2num = dec_mid2num(prev_mid);
    cout << "Dec prev mid2num: " << prev_mid2num << endl;

    vi prev_perm = dec_mid2perm(prev_num2mid);
    cout << "Prev mid to perm: ";
    print_perm(prev_perm);

    num = 100;
    num2mid = dec_num2mid(perm.size(), num);
    cout << "Dec num to mid:  100 ->";
    print_perm(num2mid);
    puts("");

    for (int i = 0; i < 10; ++i) {
        vi t = dec_prev_perm(init, i);
        printf( "Dec init prev %d with num: %d, perm:", i, dec_mid2num(dec_perm2mid(t)));
        print_perm(t);
    }

}

#endif // !DECREASE_H
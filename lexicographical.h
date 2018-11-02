#ifndef LEXICOGRAPHICAL_H
#define LEXICOGRAPHICAL_H

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

int lex_perm2num(const vi& perm) {
    int ret = 0;
    int n = perm.size();
    for (int i = 0; i < n-1; ++i) {
        int k = n - 1 - i;
        int num_smaller = perm[i] - 1;
        for (int j = 0; j < i; ++j) 
            if (perm[j] < perm[i])
                num_smaller--;
        ret += fact[k] * num_smaller;
    }
    return ret;
}

vi lex_num2mid(int n, int num) {
    vi mid;
    for (int i = n-1; i >= 1; --i) {
        int k = num / fact[i];
        mid.push_back(k);
        num -= k * fact[i];
    }
    return mid;
}

int lex_mid2num(vi mid) {
    int ret = 0;
    int k = mid.size();
    for (int i = 0; i < k; ++i, --k) {
        ret += fact[k] * mid[i];
    }
    return ret;
}

vi lex_perm2mid(vi perm) {
    vi mid;
    int n = perm.size();
    for (int i =0; i < n-1; ++i) {
        int num_smaller = perm[i] - 1;
        for (int j =0; j < i; ++j) {
            if (perm[j] < perm[i])
                num_smaller-=1;
        }
        mid.push_back(num_smaller);
    }
    return mid;
}

vi lex_mid2perm(vi mid) {
    // mid.size() + 1 == perm.size()
    int num = mid.size() + 1;
    vi  perm(num, 0);
    vector<bool> inuse(num+1, false);
    perm[0] = mid[0] + 1;
    inuse[perm[0]] = true;
    for (int i = 1; i < mid.size(); ++i) {
        int cur = mid[i];
        int num_smaller;
        do {
            num_smaller = 0;
            cur+=1;
            for (int j = 1; j < cur; ++j) {
                if (!inuse[j])
                    num_smaller+=1;
            }
        } while ((num_smaller < mid[i] || inuse[cur]) && cur < num);
        perm[i] = cur;
        inuse[cur] = true;
    }
    for (int i = 1; i <= perm.size(); ++i) if (!inuse[i]) {
        perm[num-1] = i;
        break;
    }
    return perm;
}

vi lex_prev_perm(const vi cur_perm, int prev_num) {
    int num = lex_perm2num(cur_perm);
    num -= prev_num;
    vi prev_mid = lex_num2mid(cur_perm.size(), num);
    vi prev_perm = lex_mid2perm(prev_mid);
    return prev_perm;
}

void lex_test() {
    int init[8] = {8, 3, 6, 7, 4, 5, 2, 1}; // 7 * 7! + 2 * 6! + 4 * 5! + 4 * 4! + 2 * 3! + 2 * 2! + 1 * 1!
    vi vinit(8);
    for (int i = 0; i < 8; ++i) vinit[i] = init[i];
    for (int i = 0; i < 2018; ++i) {
        vi cur = lex_prev_perm(vinit, 1);
        for (int j = 0; j < vinit.size(); j++) {
            vinit[j] = cur[j];
        }
    }
    cout << "Test lexicographical:";
    print_perm(vinit);
}

#endif
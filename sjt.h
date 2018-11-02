#ifndef SJT_H
#define SJT_H

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

const int LEFT = 1;
const int RIGHT = 0;

vi sjt_perm2mid(vi perm, vi &dir) {
    int size = perm.size();
    vi mid(size+1, 0);
    vi pos(size+1, 0);
    for (int i = 0; i < size; ++i) {
        pos[perm[i]] = i;
    }
    // cout << "SJT init pos:  "; print_perm(pos);
    for (int i = 2; i <= size; ++i) {
        int k = pos[i];
        if (i > 2) {
            if (i & 1) {
                dir[i] = (mid[i-1] & 1) ? RIGHT : LEFT;
            } else {
                dir[i] = ((mid[i-1] + mid[i-2]) & 1) ? RIGHT : LEFT;
            }
        } else {
            dir[2] = LEFT;
        }
        int num_smaller = 0;
        if (dir[i] == LEFT) {
            for (int j = k+1; j < size; ++j) {
                if (perm[j] < i) num_smaller++;
            }
        } else {
            for (int j = k-1; j >= 0; --j) {
                 if (perm[j] < i)
                     num_smaller++;
            }
        }
        mid[i] = num_smaller;
    }
    // stores a_n, a_(n-1), ..., a2
    std::reverse(mid.begin(), mid.end());
    mid.resize(size-1);
    return mid;
}

int sjt_mid2num(vi mid) {
    int ret = 0;
    int k = 2;
    for (int i = mid.size()-1; i >= 0; --i, ++k) {
        ret *= k;
        ret += mid[i];
    }
    return ret;
}

vi  sjt_num2mid(int size, int num) {
    vi ret;
    // stores order: a_n, a_(n-1), ..., a2
    while (num && size > 0) {
        ret.push_back(num % size);
        num /= size;
        size--;
    }
    return ret;
}

vi  sjt_mid2perm(vi mid, const vi &dir) {
    int size = mid.size() + 1;
    vi perm(size, 0);
    int delta;
    for (int i = size; i >= 2; --i) {
        if (i > 2) {
            if (i & 1) {
                delta = mid[size-(i-1)]; 
            } else {
                delta = mid[size-(i-1)]+mid[size-(i-2)];
            }
        } else {
            delta = 0;
        }
        
        if (delta & 1) {
            int num_smaller = 0;
            int j = 0;
            for (; num_smaller < mid[size-i]; j++) {
                if (perm[j] == 0) num_smaller++;
            }
            while (perm[j] != 0) j++;
            perm[j] = i;
        } else {
            int num_smaller = 0;
            int j = perm.size() - 1;
            for (; num_smaller < mid[size-i]; j--) {
                if (perm[j] == 0) num_smaller++;
            }
            while (perm[j] != 0) j--;
            perm[j] = i;
        }
    }
    for (int i = 0; i < perm.size(); ++i) {
        if (perm[i] == 0) {
            perm[i] = 1;
            break;
        }
    }
    return perm;
}

vi  sjt_prev_perm(vi perm, int prev_num) {
    int size = perm.size();
    vi dir(size+1);
    vi mid = sjt_perm2mid(perm, dir);
    int num = sjt_mid2num(mid);
    num -= prev_num;
    mid = sjt_num2mid(size, num);
    vi prev = sjt_mid2perm(mid, dir);
    return prev;
}

void sjt_test() {
    vi init = {8, 3, 9, 6, 4, 7, 5, 2, 1};
    vi dir(init.size()+1, 0);
    vi mid = sjt_perm2mid(init, dir);
    cout << "SJT init perm  : "; print_perm(init);
    cout << "SJT init dir   : "; print_perm(dir);
    cout << "SJT perm to mid: "; print_perm(mid);
    vi perm = sjt_mid2perm(mid, dir);
    cout << "SJT mid to perm: "; print_perm(perm);

    perm = {8, 3, 6, 7, 4, 5, 2, 1};
    for (int i = 0; i < 10; ++i) {
        cout << "SJT init prev " << i << " with num: ";
        vi prev = sjt_prev_perm(perm, i);
        cout << sjt_mid2num(sjt_perm2mid(prev, dir));
        cout << ", perm:"; print_perm(prev);
    }
}

#endif

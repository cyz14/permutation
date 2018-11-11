#include "lexicographical.h"
#include "increase.h"
#include "decrease.h"
#include "sjt.h"

#include <ctime>
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
int fact[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
vi init = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

void test_size(int size) {
    vi perm = init;
    perm.resize(size);
    clock_t t = clock();
    for (int i = 0; i < fact[perm.size()] - 1; ++i) {
        vi tmp = lex_next_perm(perm);
        // print_perm(tmp);
        perm = tmp;
    }
    t = clock() - t;
    printf("Lex time used for %d: %.3f\n", size, (float)t/CLOCKS_PER_SEC );
    
    perm = init;
    perm.resize(size);
    // print_perm(perm);
    t = clock();
    for (int i = 0; i < fact[perm.size()] - 1; ++i) {
        vi tmp = inc_next_perm(perm);
        // print_perm(tmp);
        perm = tmp;
    }
    t = clock() - t;
    printf("Inc time used for %d: %.3f\n", size, (float)t/CLOCKS_PER_SEC );

    perm = init;
    perm.resize(size);
    t = clock();
    for (int i = 0; i < fact[perm.size()] - 1; ++i) {
        vi tmp = dec_next_perm(perm);
        // print_perm(tmp);
        perm = tmp;
    }
    t = clock() - t;
    printf("Dec time used for %d: %.3f\n", size, (float)t/CLOCKS_PER_SEC );

    perm = init;
    perm.resize(size);
    // print_perm(perm);
    t = clock();
    for (int i = 0; i < fact[perm.size()] - 1; ++i) {
        vi tmp = sjt_next_perm(perm);
        // print_perm(tmp);
        perm = tmp;
    }
    t = clock() - t;
    printf("SJT time used for %d: %.3f\n", size, (float)t/CLOCKS_PER_SEC );
}

void test_all() {
    for (int size = 3; size < 10; ++size) {
        cout << "Test size " << size << ":" << endl;
        test_size(size);
    }
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        int size = atoi(argv[1]);
        test_size(size);
    } else {
        cout << "Usage: ./time_test num" << endl;
        cout << "Test all..." << endl;
        test_all();
    }
    return 0;
}
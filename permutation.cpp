#include "lexicographical.h"
#include "increase.h"
#include "decrease.h"
#include "sjt.h"

#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
int fact[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

void print_perm(vi perm) {
    for (auto i : perm) cout << ' ' << i;
    cout << endl;
}

void usage() {
    printf("Usage: ./permutation [prev_number]\n"
           "    input: size p_1, p_2, ..., p_size\n"
           "    e.g.: ./permutation 2018 < init.txt\n"
    );
}

int main(int argc, char* argv[]) {
    // -std=c++11
    vi init;// = {8, 3, 6, 7, 4, 5, 2, 1};
    // 7 * 7! + 2 * 6! + 4 * 5! + 4 * 4! + 2 * 3! + 2 * 2! + 1 * 1!
    int size = 0;
    cin >> size;
    for (int i = 0; i < size; ++i) {
        int t; cin >> t;
        init.push_back(t);
    }

    int prev = 0;
    if (argc == 2) {
       prev = atoi(argv[1]);
    } else {
        prev = 2018;
    }

    // 1. lexicographical
    // lex_test
    cout << "Lex init perm:"; print_perm(init);
    vi perm = lex_prev_perm(init, prev);
    printf( "Lex prev %4d:", prev);
    print_perm(perm);
    cout << endl;

    // 2. increase
    // inc_test();
    cout << "Inc init perm:"; print_perm(init);
    perm = inc_prev_perm(init, prev);
    printf( "Inc prev %4d:", prev);
    print_perm(perm);
    puts("");

    // 3. decrease
    // dec_test();
    cout << "Dec init perm:"; print_perm(init);
    perm = dec_prev_perm(init, prev);
    printf( "Dec prev %4d:", prev);
    print_perm(perm);
    puts("");

    // 4. SJT
    // sjt_test();
    cout << "SJT init perm:"; print_perm(init);
    perm = sjt_prev_perm(init, prev);
    printf( "SJT prev %4d:", prev);
    print_perm(perm);

    return 0;
}

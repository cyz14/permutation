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

int main() {
    
    lex_test();

    inc_test();

    dec_test();

    sjt_test();

    return 0;
}
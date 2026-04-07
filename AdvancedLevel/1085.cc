#include <bits/stdc++.h>
int main() {
    unsigned sLen, p;
    std::cin >> sLen >> p;
    std::vector<unsigned> seq( sLen );
    for ( auto& e : seq ) {
        std::cin >> e;
    }
    std::ranges::sort( seq );
    unsigned len = 1;
    for ( unsigned i = 0; i < sLen - len /* REMAIN NUMBERS HAVE NO POTENTIAL TO BEAT CURRENT BEST*/; i++ ) {
        unsigned count = std::upper_bound( seq.begin() + i, seq.end(), (long long)p * seq[i] /* This can go over 10^19 */ ) - seq.begin() - i;
        len = std::max( count, len );
    }
    std::cout << len;
}

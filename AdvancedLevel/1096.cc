#include <bits/stdc++.h>
using ull = unsigned long long;
int main() {
    ull num;
    std::cin >> num;
    std::vector<ull> csctSeq;
    ull sqrtLimit = std::sqrt( num );
    for ( ull i = 2; i <= sqrtLimit; i++ ) {
        if ( num % i == 0 ) {
            std::vector<ull> seq{ i };
            auto factorial = i;
            for ( int offset = 1; offset <= 30; offset++ ) {
                factorial *= ( i + offset );
                if ( num % factorial == 0 ) {
                    seq.push_back( i + offset );
                } else {
                    break;
                }
            }
            if ( csctSeq.empty() || seq.size() > csctSeq.size() ) {
                csctSeq = std::move( seq );
            }
        }
    }
    if ( csctSeq.empty() ) {
        csctSeq = { num };
    }
    std::cout << csctSeq.size() << "\n";
    for ( size_t i = 0; i < csctSeq.size(); i++ ) {
        std::cout << ( i ? "*" : "" ) << csctSeq[i];
    }
    return 0;
}

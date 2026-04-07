#include <bits/stdc++.h>
int main() {
    int memberN, maxHandN = 0, maxHand = 0;
    double rPrice, incPercent;
    std::cin >> memberN >> rPrice >> incPercent;
    std::vector retailers( memberN, std::vector<int>{} );
    int root;
    for ( int i = 0, spl; i < memberN; i++ ) {
        std::cin >> spl;
        if ( spl == -1 ) {
            root = i;
        } else {
            retailers[spl].push_back( i );
        }
    }
    std::queue q{ std::deque{ std::pair{ root, 0 } } };
    while ( !q.empty() ) {
        auto [i, hand] = q.front();
        q.pop();
        if ( hand > maxHand ) {
            maxHand = hand;
            maxHandN = 1;
        } else if ( hand == maxHand ) {
            maxHandN++;
        }
        for ( int nextI : retailers[i] ) {
            q.emplace( nextI, hand + 1 );
        }
    }
    printf( "%.2f %d", rPrice * std::pow( 1 + incPercent / 100, maxHand ), maxHandN );
}

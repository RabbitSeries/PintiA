#include <bits/stdc++.h>
using namespace std;
int main() {
    int memberCnt;
    double rootPrice, delta;
    cin >> memberCnt >> rootPrice >> delta;
    vector<pair<vector<int>, int>> chain( memberCnt );
    for ( int childCnt; auto& [childs, productCnt] : chain ) {
        cin >> childCnt;
        if ( childCnt == 0 ) {
            cin >> productCnt;
            continue;
        }
        childs.resize( childCnt );
        for ( int i : views::iota( 0, childCnt ) ) {
            cin >> childs[i];
        }
    }
    queue<pair<int, double>> q( { { 0, rootPrice } } );
    double res = 0;
    while ( !q.empty() ) {
        auto [curId, curPrice] = q.front();
        q.pop();
        auto& [nextvList, productCnt] = chain[curId];
        if ( nextvList.empty() ) {
            res += productCnt * curPrice;
            continue;
        }
        for ( int nextv : nextvList ) {
            q.emplace( nextv, ( 1 + delta/100 ) * curPrice );
        }
    }
    cout << fixed << setprecision( 1 ) << res;
}
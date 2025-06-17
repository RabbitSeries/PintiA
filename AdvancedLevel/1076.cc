#include <bits/stdc++.h>
using namespace std;
int main() {
    int userCnt, countLevel, queryCnt;
    cin >> userCnt >> countLevel;
    vector<vector<int>> followers( userCnt + 1 );
    for ( int listSize; int i : views::iota( 1, userCnt + 1 ) ) {
        cin >> listSize;
        for ( int j = 0, follow; j < listSize; j++ ) {
            cin >> follow;
            followers[follow].emplace_back( i );
        }
    }
    cin >> queryCnt;
    for ( int i = 0, queryUser; i < queryCnt; i++ ) {
        cin >> queryUser;
        vector<int> q( { queryUser } );
        vector<bool> curVisited( userCnt + 1, false );
        curVisited[queryUser] = true;
        int level = 0, res = 0;
        while ( level++ < countLevel && !q.empty() ) {
            vector<int> curQ = move( q );
            q.resize( 0 );
            for ( int& curUser : curQ ) {
                for ( auto& nextv : followers[curUser] ) {
                    if ( !curVisited[nextv] ) {
                        curVisited[nextv] = true;
                        q.emplace_back( nextv );
                        res++;
                    }
                }
            }
        }
        cout << res << endl;
    }
}
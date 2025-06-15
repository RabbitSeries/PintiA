#include <bits/stdc++.h>
using namespace std;
// This problem is also disgusting, please explain how to avoid excceed the maximum capacity
using pos = tuple<int, int, vector<int>>;
int capacity, cityCnt, destination, roadCnt;
int minRequired = INT_MAX, minTake = INT_MAX;
vector<int> resPath, bikeMap;
vector<vector<pair<int, int>>> cityMap;
void optimizePath( vector<int>&& path ) {
    int required = 0, take = 0;
    int limit = capacity / 2;
    for ( int p : path ) {                                     // required: limit - bikeMap.at( p )
        required += max( limit - bikeMap.at( p ) - take, 0 );  // if required is positive then require more if higher than current holding, otherwise require nothing
        take -= min( limit - bikeMap.at( p ), take );          // if required is negative then takeaway, otherwise take from current holding as many as possible
    }
    if ( required < minRequired || ( required == minRequired && take < minTake ) ) {
        minRequired = required;
        minTake = take;
        resPath = move( path );
    }
}
void Dijkstra() {
    vector<int> cost( cityCnt + 1, INT_MAX );
    priority_queue<pos, vector<pos>, greater<>> pq;
    pq.emplace( 0, 0, vector<int>{} );
    cost[0] = 0;
    while ( !pq.empty() ) {
        auto [curCost, curId, curPath] = move( const_cast<decltype( pq )::value_type&>( pq.top() ) );
        pq.pop();
        if ( !resPath.empty() && curId != destination ) {
            break;
        } else if ( curCost > cost[curId] ) {
            continue;
        }
        if ( curId != 0 ) {
            curPath.emplace_back( curId );
        }
        if ( curId == destination ) {
            optimizePath( move( curPath ) );
            continue;
        }
        for ( auto [nextId, dis] : cityMap.at( curId ) ) {
            int nextCost = curCost + dis;
            if ( nextCost <= cost[nextId] ) {
                cost[nextId] = nextCost;
                pq.emplace( nextCost, nextId, curPath );
            }
        }
    }
}
int main() {
    cin >> capacity >> cityCnt >> destination >> roadCnt;
    bikeMap.resize( cityCnt + 1 );
    cityMap.resize( cityCnt + 1 );
    for ( int i = 1; i <= cityCnt; i++ ) {
        cin >> bikeMap[i];
    }
    for ( int i = 0; i < roadCnt; i++ ) {
        int source, dest, cost;
        cin >> source >> dest >> cost;
        cityMap[source].emplace_back( dest, cost );
        cityMap[dest].emplace_back( source, cost );
    }
    Dijkstra();
    cout << minRequired << " " << 0;
    for ( int p : resPath ) {
        cout << "->" << p;
    }
    cout << " " << minTake;
}
#include <bits/stdc++.h>
using namespace std;
int main() {
    double capacity, distance, disPerGasUnit, stationCnt, maxDist = 0;
    cin >> capacity >> distance >> disPerGasUnit >> stationCnt;
    vector<pair<double, double>> stationInfo( stationCnt );  // (dist price)
    for ( int i = 0; i < stationCnt; i++ ) {
        cin >> stationInfo[i].second >> stationInfo[i].first;
    }
    sort( stationInfo.begin(), stationInfo.end() );
    if ( stationInfo[0].first != 0 ) {
        cout << "The maximum travel distance = 0.00" << endl;
        return 0;
    }
    stationInfo.emplace_back( distance, 0 );     // The last place (destination) must have the lowest fee, so that any former station will arrive with empty tank
    using feeInfo = tuple<double, int, double>;  // (curFee, curPos, curGasRemain)
    priority_queue<feeInfo, vector<feeInfo>, greater<>> pq;
    vector<unordered_map<double, double>> fee( stationCnt + 1 );  // remainGas, fee
    fee[0][0] = 0;
    pq.emplace( 0, 0, 0 );
    while ( !pq.empty() ) {
        auto [curFee, curPos, curGasRemain] = pq.top();
        pq.pop();
        if ( curFee > fee[curPos][curGasRemain] ) {
            continue;
        }
        if ( curPos == stationCnt ) {
            cout << fixed << setprecision( 2 ) << curFee << endl;
            return 0;
        }
        auto& [curDis, curPrice] = stationInfo[curPos];
        for ( int nextPos = curPos + 1; nextPos <= stationCnt; nextPos++ ) {
            auto& [nextDis, nextPrice] = stationInfo[nextPos];
            double gasRequired = ( nextDis - curDis ) / disPerGasUnit;
            if ( gasRequired > capacity ) {  // Can't make it to the next station, just calculate the maximum distance.
                maxDist = max( capacity * disPerGasUnit + curDis, maxDist );
                break;  // And futher stations are not reachable
            }
            double fillTo = curPrice < nextPrice ? capacity : gasRequired;           // Otherwise, if current station's fuel is cheaper you can choose to either have a full fill or fill to the next station
            double nextFee = curFee + curPrice * max( fillTo - curGasRemain, 0.0 );  // But full fill will save more money, because fewer fuel will be filled on the next station.
            double nextGasRemain = fillTo - gasRequired;
            if ( !fee[nextPos].contains( nextGasRemain ) || nextFee < fee[nextPos][nextGasRemain] ) {
                fee[nextPos][nextGasRemain] = nextFee;
                pq.emplace( nextFee, nextPos, nextGasRemain );
            }
        }
    }
    cout << "The maximum travel distance = " << fixed << setprecision( 2 ) << maxDist;
    return 0;
}
// double maxFillFee = curFee + ( capacity - curGasRemain ) * stationInfo[curPos].first; // Simply try two way
// if ( !fee[nextPos].contains( capacity - gasRequired ) || maxFillFee < fee[nextPos][capacity - gasRequired] ) {
//     fee[nextPos][capacity - gasRequired] = maxFillFee;
//     pq.emplace( maxFillFee, nextPos, capacity - gasRequired );
// }
// double nextFee = ( max( gasRequired, curGasRemain ) - curGasRemain ) * stationInfo[curPos].first + curFee;
// double nextGasRemain = max( curGasRemain - gasRequired, (double)0 );
// if ( !fee[nextPos].contains( nextGasRemain ) || nextFee < fee[nextPos][nextGasRemain] ) {
//     fee[nextPos][nextGasRemain] = nextFee;
//     pq.emplace( nextFee, nextPos, nextGasRemain );
// }
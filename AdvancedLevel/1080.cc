#include <bits/stdc++.h>
using namespace std;
struct stuInfo {
    int stuId, gradeSum;
    vector<int> grades{ 0, 0 }, choices;
    bool operator>( stuInfo const& rhs ) const {
        if ( gradeSum != rhs.gradeSum ) {
            return gradeSum > rhs.gradeSum;
        }
        return grades[0] > rhs.grades[0];
    }
    bool operator==( stuInfo const& rhs ) const {
        return gradeSum == rhs.gradeSum && grades[0] == rhs.grades[0];
    }
};
int main() {
    int stuCnt, schoolCnt, choiceCnt;
    cin >> stuCnt >> schoolCnt >> choiceCnt;
    vector<size_t> quotas( schoolCnt );
    vector<vector<pair<int, int>>> admLists( schoolCnt );  // (stuId, indexId in stuInfos)
    for ( int i : views::iota( 0, schoolCnt ) ) {
        cin >> quotas[i];
    }
    vector<stuInfo> stuInfos( stuCnt );
    for ( int i = 0; stuInfo& info : stuInfos ) {
        info.stuId = i++;
        for ( int j : views::iota( 0, 2 ) ) {
            cin >> info.grades[j];
        }
        info.gradeSum = accumulate( info.grades.begin(), info.grades.end(), 0, plus<>{} );
        info.choices.resize( choiceCnt );
        for ( int j : views::iota( 0, choiceCnt ) ) {
            cin >> info.choices[j];
        }
    }
    sort( stuInfos.begin(), stuInfos.end(), greater<>{} );
    for ( int i : views::iota( 0, stuCnt ) ) {
        auto const& info = stuInfos[i];
        for ( int schl : info.choices ) {
            if ( admLists[schl].size() < quotas[schl] || stuInfos[admLists[schl].back().second] == info ) {
                admLists[schl].emplace_back( info.stuId, i );
                break;
            }
        }
    }
    for ( auto& admList : admLists ) {
        sort( admList.begin(), admList.end() );
        for ( size_t i : views::iota( 0ull, admList.size() ) ) {
            cout << ( i ? " " : "" ) << admList[i].first;
        }
        cout << endl;
    }
}
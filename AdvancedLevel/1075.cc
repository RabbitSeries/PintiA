#include <bits/stdc++.h>
using namespace std;
int userCnt, problemCnt, submissionCnt;
vector<int> problems;
struct stuInfo {
    vector<optional<int>> submits;
    stuInfo( int problemCnt ) : submits( problemCnt, nullopt ) {};
    int uid, sum = 0, solvecnt = 0, rank = 1;
    void sumScores() {
        for ( auto& grade : submits ) {
            sum += max( grade.value_or( 0 ), 0 );
        }
    }
    void countSolveCnt( vector<int> const& problems ) {
        for ( int i = 0; i < problemCnt; i++ ) {
            solvecnt += submits[i] == problems[i];
        }
    }
};
int main() {
    cin >> userCnt >> problemCnt >> submissionCnt;
    vector<stuInfo> scores( userCnt, stuInfo{ problemCnt } );
    problems.resize( problemCnt );
    for ( int i : views::iota( 0, problemCnt ) ) {
        cin >> problems[i];
    }
    while ( submissionCnt-- ) {
        int userId, problemId, grade;
        cin >> userId >> problemId >> grade;
        auto& curScore = scores[userId - 1].submits[problemId - 1];
        curScore = curScore.has_value() ? max( curScore.value(), grade ) : grade;
    }
    for ( int i : views::iota( 0, userCnt ) ) {
        scores[i].sumScores();
        scores[i].countSolveCnt( problems );
        scores[i].uid = i + 1;
    }
    sort( scores.begin(), scores.end(), [&]( stuInfo const& lhs, stuInfo const& rhs ) {
        if ( lhs.sum != rhs.sum ) {
            return lhs.sum > rhs.sum;
        } else {
            if ( lhs.solvecnt != rhs.solvecnt ) {
                return lhs.solvecnt > rhs.solvecnt;
            }
            return lhs.uid < rhs.uid;
        }
    } );
    for ( int i = 1; i < userCnt; i++ ) {
        scores[i].rank = scores[i].sum == scores[i - 1].sum ? scores[i - 1].rank : i + 1;
    }
    for ( int i = 0; i < userCnt; i++ ) {
        stuInfo& stu = scores[i];
        auto isValid = []( optional<int>& grade ) { return grade.has_value() && grade.value() >= 0; };
        if ( !any_of( stu.submits.begin(), stu.submits.end(), isValid ) ) {
            continue;
        }
        cout << stu.rank << " " << right << setfill( '0' ) << setw( 5 ) << stu.uid << " " << stu.sum;
        for ( optional<int>& grade : stu.submits ) {
            if ( !grade.has_value() ) {
                cout << " -";
            } else {
                cout << " " << max( grade.value(), 0 );
            }
        }
        cout << endl;
    }
}
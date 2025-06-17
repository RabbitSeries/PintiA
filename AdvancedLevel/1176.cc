#include <bits/stdc++.h>
using namespace std;
int rectantCnt, productCnt, equationCnt;
set<string> rectants;
vector<string> products, selections;
map<string, vector<set<string>>> equations;  // (product, lhs)
vector<int> intervals;
void printEquation( int group, int& curSelection ) {
    for ( int i = 0; i < intervals[group]; i++, curSelection++ ) {
        cout << ( i ? " + " : "" ) << selections[curSelection];
    }
    cout << " -> " << products[group] << endl;
}
void DFS( vector<int>& lhsLens, vector<string>& curSelection, int pId = 0 ) {
    if ( pId == productCnt ) {
        if ( selections.empty() || curSelection < selections ) {
            selections = curSelection;
            intervals = lhsLens;
        }
        return;
    }
    for ( auto const& lhs : equations.at( products[pId] ) ) {
        bool isOverlapping = any_of( curSelection.begin(), curSelection.end(), [&]( const string& rectant ) {
            return lhs.contains( rectant );
        } );
        if ( !isOverlapping ) {
            copy( lhs.begin(), lhs.end(), back_inserter( curSelection ) );  // also: curSelection.insert( curSelection.end(), lhs.begin(), lhs.end() );
            lhsLens.emplace_back( lhs.size() );
            DFS( lhsLens, curSelection, pId + 1 );
            curSelection.resize( curSelection.size() - lhs.size() );
            lhsLens.pop_back();
        }
    }
}
int main() {
    cin >> rectantCnt;
    for ( int i = 0; i < rectantCnt; i++ ) {
        string rectant;
        cin >> rectant;
        rectants.emplace( move( rectant ) );
    }
    cin >> productCnt;
    products.resize( productCnt );
    for ( string& p : products ) {
        cin >> p;
        if ( rectants.contains( p ) ) {
            equations[p].emplace_back( set( { p } ) );
        }
    }
    cin >> equationCnt;
    for ( int i = 0; i < equationCnt; i++ ) {
        set<string> lhs;
        for ( string rectant; ( cin >> rectant ) && rectant != "->"; ) {
            if ( rectant != "+" ) {
                lhs.emplace( move( rectant ) );
            }
        }
        if ( string product; cin >> product && all_of( lhs.begin(), lhs.end(), [&]( const string& e ) { return rectants.contains( e ); } ) ) {  // Filter
            equations[product].emplace_back( move( lhs ) );
        }
    }
    vector<int> lhsLens;
    vector<string> curSelection;
    DFS( lhsLens, curSelection );
    for ( int i = 0, selectionI = 0; i < productCnt; i++ ) {
        printEquation( i, selectionI );
    }
}

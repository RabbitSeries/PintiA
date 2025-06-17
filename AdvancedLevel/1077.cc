#include <bits/stdc++.h>
using namespace std;
int main() {
    int sentenceCnt;
    scanf( "%d\n", &sentenceCnt );
    vector<string> sentences( sentenceCnt );
    for ( int i : views::iota( 0, sentenceCnt ) ) {
        getline( cin, sentences[i] );
    }
    optional<string> res;
    for ( size_t len = 0; len < sentences[0].size(); len++ ) {
        char c = *( sentences[0].rbegin() + len );
        if ( all_of( sentences.begin() + 1, sentences.end(), [&]( const string& sentence ) {
                 return ( len < sentence.size() ) && *( len + sentence.rbegin() ) == c;
             } ) ) {
            res = res.has_value() ? ( string( 1, c ) + res.value() ) : string( 1, c );
        } else {
            break;
        }
    }
    cout << res.value_or( "nai" );
}
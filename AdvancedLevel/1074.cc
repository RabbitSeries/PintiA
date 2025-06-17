#include <bits/stdc++.h>
using namespace std;
int main() {
    string head;
    int inputSize, reverseSize;
    cin >> head >> inputSize >> reverseSize;
    unordered_map<string, pair<string, string>> linkedList;  // name, value, next
    for ( int i = 0; i < inputSize; i++ ) {
        string l, value, r;
        cin >> l >> value >> r;
        linkedList.emplace( l, pair{ value, r } );
    }
    vector<pair<string, string>> sorted;  // name value
    while ( head != "-1" ) {
        sorted.emplace_back( head, linkedList.at( head ).first );
        head = linkedList.at( head ).second;
    }
    for ( size_t i = 0; i + reverseSize <= sorted.size(); i += reverseSize ) {
        reverse( sorted.begin() + i, sorted.begin() + i + reverseSize );
    }
    for ( auto i = sorted.begin(); i != sorted.end() - 1; i++ ) {
        cout << i->first << " " << i->second << " " << next( i )->first << endl;
    }
    cout << sorted.back().first << " " << sorted.back().second << " " << -1;
}
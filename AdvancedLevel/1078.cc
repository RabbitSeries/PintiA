#include <bits/stdc++.h>
using namespace std;
bool isPrime( int num ) {
    if ( num <= 1 ) return false;
    for ( int i = 2; i <= sqrt( num ); i++ ) {
        if ( !( num % i ) ) {
            return false;
        }
    }
    return true;
}
int main() {
    int givenSize, numCnt;
    cin >> givenSize >> numCnt;
    while ( !isPrime( givenSize ) ) {  // Typical while/for loop searching for places
        givenSize++;
    }
    vector<bool> hashTable( givenSize, false );
    for ( int i = 0, num; i < numCnt; i++ ) {
        cin >> num;
        int hashPos = num % givenSize;
        for ( int j = 1; j < givenSize && hashTable[hashPos]; j++ ) {  // Typical while/for loop searching for places
            hashPos = ( num + j * j ) % givenSize;                     // Quadratic probing is based on the original number
        }
        cout << ( i ? " " : "" );
        if ( !hashTable[hashPos] ) {  // Then perform a pre assertation for post process
            hashTable[hashPos] = true;
            cout << hashPos;
        } else {
            cout << "-";
        }
    }
}
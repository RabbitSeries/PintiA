#include <bits/stdc++.h>
int main() {
    std::string str;
    std::cin >> str;
    int P_count = 0, PA_count = 0, AT_count = 0;
    for ( char c : str ) {
        if ( c== 'P' ) {
            P_count++;
        } else if ( c == 'A' ) {
            PA_count = ( PA_count + P_count ) % 1000000007;
        } else if ( c == 'T' ) {
            AT_count = ( AT_count + PA_count ) % 1000000007;
        }
    }
    std::cout << AT_count;
}

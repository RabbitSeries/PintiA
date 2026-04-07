#include <bits/stdc++.h>
int main() {
    std::string original, current;
    std::cin >> original >> current;
    std::set<char> printed;
    for ( size_t i = 0, j = 0; i < original.size(); i++ ) {
        if ( original[i] == current[j] ) {
            j++;
        } else {
            original[i] = std::toupper( original[i] );
            if ( !printed.contains( original[i] ) ) {
                std::cout << original[i];
                printed.insert( original[i] );
            }
        }
    }
}

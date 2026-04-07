#include <bits/stdc++.h>
int main() {
    std::string sell, required;
    std::cin >> sell >> required;
    std::map<char, int> sell_grouped;
    for ( char c : sell ) {
        sell_grouped[c]++;
    }
    int missing = 0;
    for ( char c : required ) {
        if ( sell_grouped[c] > 0 ) {
            sell_grouped[c]--;
        } else {
            missing++;
        }
    }
    if ( missing == 0 ) {
        std::cout << "Yes " << sell.size() - required.size();
    } else {
        std::cout << "No " << missing;
    }
}

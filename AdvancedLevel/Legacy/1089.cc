#include <bits/stdc++.h>
std::optional<std::vector<int>> insertion_sort( std::vector<int> data, std::vector<int>& compare ) {
    bool found = false;
    int len = data.size();
    for ( int i = 1; i < len; i++ ) {  // You don't have to sort by your self.
        for ( int j = i; j - 1 >= 0; j-- ) {
            if ( data[j] < data[j - 1] ) {
                std::swap( data[j], data[j - 1] );
            } else {
                break;
            }
        }
        if ( found ) {
            return data;
        }
        if ( data == compare ) {
            found = true;
        }
    }
    return std::nullopt;
}
std::optional<std::vector<int>> merge_sort( std::vector<int> data, std::vector<int>& compare ) {
    bool found = false;
    int len = data.size(), width = 1;
    std::vector<int> aux( len );
    for ( int t = 0; width < len; t++, width *= 2 ) {
        for ( int l = 0; l + width < len; l += 2 * width ) {
            int mid = l + width, r = std::min( l + 2 * width, len );
            std::copy( data.begin() + l, data.begin() + r, aux.begin() + l );
            int i = l, j = mid, k = l;
            while ( k < r ) {  // You don't have to sort by your self.
                if ( j == r || ( j < r && aux[i] <= aux[j] ) ) {
                    data[k++] = aux[i++];
                } else {
                    data[k++] = aux[j++];
                }
            }
        }
        if ( found ) {
            return data;
        }
        if ( data == compare ) {
            found = true;
        }
    }
    return std::nullopt;
}
int main() {
    int dataN;
    std::cin >> dataN;
    std::vector<int> data( dataN ), partial_sorted( dataN );
    for ( int& e : data ) {
        std::cin >> e;
    }
    for ( int& e : partial_sorted ) {
        std::cin >> e;
    }
    auto seq = insertion_sort( data, partial_sorted );
    if ( seq ) {
        std::cout << "Insertion Sort\n";
    } else {
        seq = merge_sort( data, partial_sorted );
        std::cout << "Merge Sort\n";
    }
    auto& r = seq.value();
    std::cout << std::accumulate( r.begin(), r.end(), std::string(), []( const std::string& a, int b ) {
        return ( a.empty() ? a : ( a + " " ) ) + std::to_string( b );
    } );
}

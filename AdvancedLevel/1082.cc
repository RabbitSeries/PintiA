#include <bits/stdc++.h>
using sv = std::string_view;
std::vector<sv> digits{ "ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu" },
    units{ "Shi", "Bai", "Qian" },
    scale{ "Wan", "Yi" },
    buffer;
void print_thousand( std::string const& snum ) {
    for ( int i = 0, len = snum.size(); i < len; i++ ) {
        if ( snum[i] == '0' ) {
            while ( i < len && snum[i] == '0' ) {  // Escape leading zeros
                i++;
            }
            if ( i < len ) {  // There are more non zerors print a "ling", then print later on digits
                buffer.push_back( digits[0] );
            } else {
                return;
            }
        }
        buffer.push_back( digits[snum[i] - '0'] );
        if ( len - i - 2 >= 0 ) {  // Remain length len - i 's unit
            buffer.push_back( units[len - i - 2] );
        }
    }
}
int main() {
    int num;
    std::cin >> num;
    if ( num < 0 ) {
        buffer.push_back( "Fu" );
        num = -num;
    }
    std::string snum = std::to_string( num );
    for ( int i = 0, len = snum.size(), print_len; i < len; ) {
        if ( snum[i] == '0' ) {
            while ( i < len && snum[i] == '0' ) {
                i++;
            }
            if ( i < len || buffer.empty() ) {  // If escaped zero will confront more non-zero digits, print a "ling"
                buffer.push_back( digits[0] );
            }
            continue;
        }
        print_len = ( len - i ) % 4 == 0 ? 4 : ( len - i ) % 4;  // Print no more than 4 digits at a time, make the remainning len-i the intergral times of 4
        print_thousand( snum.substr( i, print_len ) );
        if ( ( len - i - print_len ) / 4 >= 1 ) {  // If remainning numer is longer than 4 digits, print scale "Wan" or "Yi"
            buffer.push_back( scale[( len - i - print_len ) / 4 - 1] );
        }
        i += print_len;
    }
    std::cout << std::accumulate( buffer.begin(), buffer.end(), std::string{}, []( const std::string& s1, const sv& s2 ) {
        return s1.empty() ? s2.data() : ( s1 + " " + s2.data() );
    } );
}

#include <bits/stdc++.h>
using ll = long int;
ll gcd( ll a, ll b ) { return b == 0 ? a : gcd( b, a % b ); }
void format( ll numerator, ll denominator ) {
    bool sign = false;
    sign ^= numerator * denominator < 0;
    numerator = std::abs( numerator );
    denominator = std::abs( denominator );
    if ( denominator == 0 ) {
        std::cout << ( sign ? "-Inf" : "Inf" );
        return;
    }
    if ( sign ) {
        std::cout << "(-";
    }
    ll dn_gcd = gcd( numerator, denominator );
    numerator /= dn_gcd;
    denominator /= dn_gcd;
    if ( denominator == 1 ) {
        std::cout << numerator;
    } else {
        ll carrier = numerator / denominator;
        numerator -= carrier * denominator;
        if ( carrier > 0 ) {
            std::cout << carrier << " ";
        }
        std::cout << numerator << "/" << denominator;
    }
    if ( sign ) {
        std::cout << ")";
    }
}
int main() {
    ll a, b, c, d;
    scanf( "%ld/%ld%ld/%ld", &a, &b, &c, &d );
    // clang-format off
    format( a, b ); std::cout << " + "; format( c, d ); std::cout << " = "; format( a * d + c * b, b * d ); std::cout << "\n";
    format( a, b ); std::cout << " - "; format( c, d ); std::cout << " = "; format( a * d - c * b, b * d ); std::cout << "\n";
    format( a, b ); std::cout << " * "; format( c, d ); std::cout << " = "; format( a * c, b * d );         std::cout << "\n"; 
    format( a, b ); std::cout << " / "; format( c, d ); std::cout << " = "; format( a * d, b * c );         std::cout << "\n";
}

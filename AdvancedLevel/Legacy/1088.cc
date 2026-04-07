#include <bits/stdc++.h>
using ll = long int;
ll gcd( ll a, ll b ) {
    return b == 0 ? a : gcd( b, a % b );
}
ll lcm( ll a, ll b ) {
    return a / gcd( a, b ) * b;
}
struct fraction {
    bool sign = false;
    ll carrier = 0, numerator = 0, denominator = 1;
    fraction( bool s, ll c, ll n, ll d ) : sign{ s }, carrier{ c }, numerator{ n }, denominator{ d } {}
    fraction() {}
    static fraction sci_fraction( ll n, ll d ) {
        return fraction( 0, 0, n, d );
    }
    std::string print() const {
        std::string builder;
        if ( denominator == 0 ) {
            return sign ? "-Inf" : "Inf";
        } else {
            builder = std::to_string( numerator );
            if ( denominator != 1 ) {  // Make integer live in numerator
                builder += "/" + std::to_string( denominator );
            }
        }
        if ( carrier != 0 ) {
            builder = std::to_string( carrier ) + " " + builder;
        }
        if ( sign ) {
            builder = "(-" + builder + ")";
        }
        return builder;
    }
    friend std::ostream& operator<<( std::ostream& os, const fraction& frac ) {
        os << frac.print();
        return os;
    }
    fraction rational_to_sci() const {
        return sci_fraction( ( sign ? -1 : 1 ) * ( numerator + carrier * denominator ), denominator );
    }
    fraction sci_to_rational() const {
        fraction r( 0, 0, numerator, denominator );
        if ( r.numerator < 0 ) {
            r.sign = 1;
            r.numerator = -r.numerator;
        }
        if ( r.denominator == 0 ) {
            return r;
        }
        ll dn_gcd = gcd( r.numerator, r.denominator );
        r.denominator /= dn_gcd;
        r.numerator /= dn_gcd;
        if ( r.denominator != 1 ) {
            r.carrier += r.numerator / r.denominator;
            r.numerator -= ( r.numerator / r.denominator ) * r.denominator;
        }
        return r;
    }
    friend fraction operator+( fraction const& a, fraction const& b ) {
        ll denominator = lcm( a.denominator, b.denominator );
        ll numerator = a.numerator * denominator / a.denominator + b.numerator * denominator / b.denominator;
        return sci_fraction( numerator, denominator ).sci_to_rational();
    }
    friend fraction operator-( fraction const& a, fraction const& b ) {
        ll denominator = lcm( a.denominator, b.denominator );
        ll numerator = a.numerator * denominator / a.denominator - b.numerator * denominator / b.denominator;
        return sci_fraction( numerator, denominator ).sci_to_rational();
    }
    friend fraction operator*( fraction const& a, fraction const& b ) {
        return sci_fraction( a.numerator * b.numerator, a.denominator * b.denominator ).sci_to_rational();
    }
    friend fraction operator/( fraction const& a, fraction const& b ) {
        bool sign = false;
        if ( a.numerator < 0 ) {
            sign ^= 1;
        }
        if ( b.numerator < 0 ) {
            sign ^= 1;
        }
        if ( b.numerator == 0 ) {
            return { sign, 0, 1, 0 };
        }
        ll numerator = std::abs( a.numerator * b.denominator );
        ll denominator = std::abs( a.denominator * b.numerator );
        return sci_fraction( ( sign ? -1 : 1 ) * numerator, denominator ).sci_to_rational();
    }
};
int main() {
    fraction a, b;
    char c;
    std::cin >> a.numerator >> c >> a.denominator >> b.numerator >> c >> b.denominator;
    auto plus = a + b, minus = a - b, multiply = a * b, devide = a / b;
    a = a.sci_to_rational();
    b = b.sci_to_rational();
    std::cout << a << " + " << b << " = " << plus << "\n";
    std::cout << a << " - " << b << " = " << minus << "\n";
    std::cout << a << " * " << b << " = " << multiply << "\n";
    std::cout << a << " / " << b << " = " << devide << "\n";
}

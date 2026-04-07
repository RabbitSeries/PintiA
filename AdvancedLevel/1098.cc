#include <bits/stdc++.h>
using Vec = std::vector<int>;
bool isInsertSort( const Vec& original, Vec& intermediate ) {
    auto copy = original;
    for ( size_t i = 1; i < copy.size(); i++ ) {
        // std::lower_bound then move the elements is more efficient, but not neccessary in the time complexity allowence.
        std::sort( copy.begin(), copy.begin() + i + 1 );
        if ( copy == intermediate ) {
            if ( i + 1 < copy.size() ) {
                std::sort( intermediate.begin(), intermediate.begin() + i + 2 );
            }
            return true;
        }
    }
    return false;
}
bool isHeapSort( const Vec& original, Vec& intermediate ) {
    auto copy = original;
    auto siftDown = [&]( int start, int end ) {
        while ( start < end ) {
            // Again, note l should be (start+1)*2 -1, r should be (start+1)*2+1-1
            int l = start * 2 + 1, r = start * 2 + 2, child = l;
            if ( r < end && copy[r] > copy[l] ) {
                child = r;
            }
            if ( child < end && copy[child] > copy[start] ) {
                std::swap( copy[start], copy[child] );
                start = child;
            } else {
                break;
            }
        }
    };
    // Heapify
    for ( int p = copy.size() / 2; p >= 0; p-- ) {
        siftDown( p, copy.size() );
    }
    // Extract the largest to the last place
    for ( size_t end = copy.size() - 1; end >= 1; end-- ) {
        std::swap( copy[end], copy[0] );
        siftDown( 0, end );
        if ( copy == intermediate ) {
            if ( end - 1 >= 1 ) {
                std::swap( copy[end - 1], copy[0] );
                siftDown( 0, end - 1 );
            }
            intermediate = std::move( copy );
            return true;
        }
    }
    return false;
}
int main() {
    int numN;
    std::cin >> numN;
    std::vector<int> nums( numN ), intermediate( numN );
    for ( int i = 0; i < numN; i++ ) {
        std::cin >> nums[i];
    }
    for ( int i = 0; i < numN; i++ ) {
        std::cin >> intermediate[i];
    }
    if ( isInsertSort( nums, intermediate ) ) {
        std::cout << "Insertion Sort\n";
    } else if ( isHeapSort( nums, intermediate ) ) {
        std::cout << "Heap Sort\n";
    }
    for ( int i = 0; i < numN; i++ ) {
        std::cout << ( i ? " " : "" ) << intermediate[i];
    }
    return 0;
}
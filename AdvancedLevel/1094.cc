#include <bits/stdc++.h>
int main() {
    int memberN, familyN;
    std::cin >> memberN >> familyN;
    std::unordered_map<int, std::vector<int>> hierarchy;
    for ( int parentId, childN; familyN--; ) {
        std::cin >> parentId >> childN;
        for ( int child, j = 0; j < childN; j++ ) {
            std::cin >> child;
            hierarchy[parentId].push_back( child );
        }
    }
    std::queue<int> q;
    q.push( 1 );
    size_t level = 1, count = 1;
    for ( int t = 1; !q.empty(); t++ ) {
        if ( q.size() > count ) {
            count = q.size();
            level = t;
        }
        auto curLevel = std::move( q );
        while ( !curLevel.empty() ) {
            auto id = curLevel.front();
            curLevel.pop();
            if ( hierarchy.contains( id ) ) {
                for ( auto child : hierarchy[id] ) {
                    q.push( child );
                }
            }
        }
    }
    std::cout << count << " " << level;
    return 0;
}

#include <bits/stdc++.h>
struct Node {
    int addr, key, next;
};
using SequenceLink = std::vector<std::shared_ptr<Node>>;
void printLink( const SequenceLink& seq ) {
    for ( size_t i = 0; i < seq.size(); i++ ) {
        auto p = seq[i];
        int nextAddr = i + 1 < seq.size() ? seq[i + 1]->addr : -1;
        printf( nextAddr == -1 ? "%05d %d %d\n" : "%05d %d %05d\n", p->addr, p->key, nextAddr );
    }
}
int main() {
    using LinkList = std::unordered_map<int, std::shared_ptr<Node>>;
    LinkList input;
    SequenceLink unique, removed;
    int root, nodeN;
    std::cin >> root >> nodeN;
    for ( int addr, key, next; nodeN--; ) {
        std::cin >> addr >> key >> next;
        input[addr] = std::make_shared<Node>( Node{ addr, key, next } );
    }
    auto p = input[root];
    std::set<int> visited;
    while ( p ) {
        if ( !visited.contains( std::abs( p->key ) ) ) {
            visited.insert( std::abs( p->key ) );
            unique.emplace_back( p );
        } else {
            removed.emplace_back( p );
        }
        p = input[p->next];
    }
    printLink( unique );
    printLink( removed );
    return 0;
}
#include <bits/stdc++.h>
struct city {
    int hpns = 0;
    std::vector<std::pair<std::string, int>> adjCityCost;
};
struct state {
    std::string name;
    int cost, happiness;
    std::vector<std::string> path;
    state( std::string n, int c, int h ) : name{ std::move( n ) }, cost{ c }, happiness{ h } {}
    bool operator>( const state& rhs ) const {
        return this->cost > rhs.cost;
    }
};
int main() {
    int cityN, roadN;
    std::string starting;
    std::cin >> cityN >> roadN >> starting;
    std::unordered_map<std::string, city> cities;
    cities.emplace( starting, city{} );
    for ( int i = 0, hpns; i < cityN - 1; i++ ) {
        std::string name;
        std::cin >> name >> hpns;
        cities[name].hpns = hpns;
    }
    for ( int i = 0; i < roadN; i++ ) {
        std::string from, to;
        int cost;
        std::cin >> from >> to >> cost;
        cities[from].adjCityCost.emplace_back( to, cost );
        cities[to].adjCityCost.emplace_back( std::move( from ), cost );  // Undirected map
    }
    std::unordered_map<std::string, int> costs{ std::pair{ starting, 0 } }, routes{ std::pair{ starting, 1 } };
    int maxHpns = 0, minEdgeN = INT_MAX;
    std::vector<std::string> resultPath;
    std::priority_queue pq( std::greater<>{}, std::vector{ state( starting, 0, 0 ) } );  // Optimize target is only cost
    while ( !pq.empty() ) {
        auto curcity = std::move( const_cast<state&>( pq.top() ) );
        auto [curName, curCost, curHappiness, curPathSize] = std::make_tuple( curcity.name, curcity.cost, curcity.happiness, (int)curcity.path.size() );
        pq.pop();
        if ( curCost > costs[curName] ) {  // Branch cutting
            continue;
        }
        if ( curName == "ROM" ) {  // End statistics
            if ( curHappiness > maxHpns || ( curHappiness == maxHpns && curHappiness / curPathSize > maxHpns / minEdgeN ) ) {
                maxHpns = curHappiness;
                minEdgeN = curPathSize;
                resultPath = std::move( curcity.path );
            }
            continue;
        }
        for ( auto const& [adjCity, adjCost] : cities[curName].adjCityCost ) {
            int nextCost = curCost + adjCost;
            if ( !costs.contains( adjCity ) || nextCost < costs[adjCity] ) {  // Positive cost, implicit cycle avoid
                auto nextState = state( adjCity, nextCost, curHappiness + cities[adjCity].hpns );
                nextState.path = curcity.path;
                nextState.path.push_back( adjCity );
                pq.emplace( std::move( nextState ) );
                routes[adjCity] = routes[curName];
                costs[adjCity] = nextCost;  // Optimize target
            } else if ( nextCost == costs[adjCity] ) {
                routes[adjCity] += routes[curName];  // DP target
            }
        }
    }
    std::cout << routes["ROM"] << " " << costs["ROM"] << " " << maxHpns << " " << ( maxHpns / minEdgeN ) << "\n";
    std::cout << starting;
    for ( auto& name : resultPath ) {
        std::cout << "->" << name;
    }
}

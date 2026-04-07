#include <bits/stdc++.h>
int seconds( std::string time ) {
    auto t = std::stoi( time.substr( 0, 2 ) );
    t = t * 60 + std::stoi( time.substr( 3, 2 ) );
    return t * 60 + std::stoi( time.substr( 6, 2 ) );
}
int main() {
    int recordN, queryN;
    std::cin >> recordN >> queryN;
    std::unordered_map<std::string, int> parkDuration;
    std::vector<std::tuple<std::string, int, bool>> records;
    std::vector<std::pair<int, bool>> filtered;
    std::set<std::string> mostParkingCars;
    int mostParkingAcc = INT_MIN;
    while ( recordN-- ) {
        std::string name, time, stat;
        std::cin >> name >> time >> stat;
        records.emplace_back( std::move( name ), seconds( time ), stat == "in" );
    }
    using Elem = const std::tuple<std::string, int, bool>&;
    std::ranges::sort( records, []( Elem e1, Elem e2 ) {
        return std::get<0>( e1 ) != std::get<0>( e2 ) ? std::get<0>( e1 ) < std::get<0>( e2 ) : std::get<1>( e1 ) < std::get<1>( e2 );
    } );
    for ( size_t i = 0; i < records.size(); i++ ) {
        const auto& [name, time, stat] = records[i];
        if ( stat && i + 1 < records.size() && name == std::get<0>( records[i + 1] ) && !std::get<2>( records[i + 1] ) ) {
            i++;
            int exitTime = std::get<1>( records[i] );
            auto& durationAcc = parkDuration[name];
            durationAcc += exitTime - time;
            if ( durationAcc >= mostParkingAcc ) {
                if ( durationAcc > mostParkingAcc ) {
                    mostParkingCars.clear();
                }
                mostParkingCars.insert( name );
                mostParkingAcc = durationAcc;
            }
            filtered.emplace_back( time, true );
            filtered.emplace_back( exitTime, false );
        }
    }
    std::ranges::sort( filtered );
    int parked = 0;
    auto itr = filtered.begin();
    while ( queryN-- ) {
        std::string time;
        std::cin >> time;
        int t = seconds( time );
        while ( itr != filtered.end() && t >= itr->first ) {
            if ( itr->second ) {
                parked++;
            } else {
                parked--;
            }
            itr++;
        }
        std::cout << parked << std::endl;
    }
    for ( auto& name : mostParkingCars ) {
        std::cout << name << " ";
    }
    printf( "%02d:%02d:%02d", mostParkingAcc / 3600, mostParkingAcc / 60 % 60, mostParkingAcc % 60 );
    return 0;
}

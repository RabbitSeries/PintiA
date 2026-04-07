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
    std::unordered_map<std::string, std::pair<int, bool>> prevRecord;
    std::vector<std::tuple<std::string, int, bool>> records;
    std::vector<std::pair<int, bool>> filtered;
    std::set<std::string> mostParkingCars;
    int mostParkingTime = INT_MIN;
    for ( int i = 0; i < recordN; i++ ) {
        std::string name, time, stat;
        std::cin >> name >> time >> stat;
        records.emplace_back( std::move( name ), seconds( time ), stat == "in" );
    }
    std::ranges::sort( records, {}, []( const auto& r ) { return std::get<1>( r ); } );
    for ( auto& [name, time, stat] : records ) {
        auto& [prev_time, prev_stat] = prevRecord[name];
        if ( stat ) {
            prev_time = time;
            prev_stat = true;
        } else if ( prev_stat ) {
            prev_stat = stat;
            auto& duration_acc = parkDuration[name];
            duration_acc += time - prev_time;
            if ( duration_acc >= mostParkingTime ) {
                if ( duration_acc > mostParkingTime ) {
                    mostParkingCars.clear();
                }
                mostParkingCars.insert( name );
                mostParkingTime = duration_acc;
            }
            filtered.emplace_back( prev_time, true );
            filtered.emplace_back( time, false );
        }
    }
    std::ranges::sort( filtered );
    int parked = 0;
    auto itr = filtered.begin();
    for ( int q = 1; q <= queryN; q++ ) {
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
#ifdef __cpp_lib_format
    std::cout << std::format( "{:02d}:{:02d}:{:02d}", mostParkingTime / 3600, mostParkingTime / 60 % 60, mostParkingTime % 60 );
#else
    printf( "%02d:%02d:%02d", mostParkingTime / 3600, mostParkingTime / 60 % 60, mostParkingTime % 60 );
#endif
    return 0;
}
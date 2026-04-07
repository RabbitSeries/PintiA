#include <bits/stdc++.h>
struct stuInfo {
    std::string name, id;
    unsigned grade;
    bool operator>( const stuInfo& rhs ) const {
        return grade > rhs.grade;
    }
};
int main() {
    int stuN;
    std::cin >> stuN;
    std::vector<stuInfo> stus( stuN );
    for ( int i = 0; i < stuN; i++ ) {
        std::cin >> stus[i].name >> stus[i].id >> stus[i].grade;
    }
    std::ranges::sort( stus, std::greater{} );
    unsigned itv_l, itv_r;
    std::cin >> itv_l >> itv_r;
    auto first = std::upper_bound( stus.begin(), stus.end(), itv_r, []( unsigned v, const stuInfo& stu ) {
        return stu.grade <= v;
    } );
    if ( first == stus.end() || first->grade < itv_l ) {
        std::cout << "NONE";
        return 0;
    }
    while ( first != stus.end() && first->grade >= itv_l ) {
        std::cout << first->name << " " << first->id << std::endl;
        first++;
    }
}

#include <bits/stdc++.h>
int dx[]{ 0, 0, 1, -1, 0, 0 };
int dy[]{ 0, 0, 0, 0, 1, -1 };
int dz[]{ 1, -1, 0, 0, 0, 0 };
int bfs( auto& slices, auto& visited, std::tuple<int, int, int> pos, int rows, int cols, int layers ) {
    int stat = 1;
    std::queue q{ std::deque{ pos } };
    while ( !q.empty() ) {
        auto [x, y, z] = q.front();
        q.pop();
        for ( int k = 0; k < 6; k++ ) {
            int nx = x + dx[k], ny = y + dy[k], nz = z + dz[k];
            if ( nx >= 0 && nx < rows && ny >= 0 && ny < cols && nz >= 0 && nz < layers && !visited[nz][nx][ny] && slices[nz][nx][ny] ) {
                visited[nz][nx][ny] = 1;
                stat++;
                q.emplace( nx, ny, nz );
            }
        }
    }
    return stat;
}
int main() {
    int rows, cols, layers, thresh, total = 0;
    std::cin >> rows >> cols >> layers >> thresh;
    std::vector slices( layers, std::vector( rows, std::vector( cols, 0 ) ) );
    std::vector visited = slices;
    for ( int z = 0; z < layers; z++ ) {
        for ( int x = 0; x < rows; x++ ) {
            for ( int y = 0; y < cols; y++ ) {
                std::cin >> slices[z][x][y];
            }
        }
    }
    for ( int z = 0; z < layers; z++ ) {
        for ( int x = 0; x < rows; x++ ) {
            for ( int y = 0, size; y < cols; y++ ) {
                if ( slices[z][x][y] && !visited[z][x][y] ) {
                    visited[z][x][y] = 1;
                    size = bfs( slices, visited, std::make_tuple( x, y, z ), rows, cols, layers );
                    total += ( size >= thresh ) * size;
                }
            }
        }
    }
    std::cout << total;
}

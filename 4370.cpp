#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

#define N 500
#define INF 0x3f3f3f3f

using namespace std;

int dis[ N ];
bool vis[ N ];
int cost[ N ][ N ];

void SPFA ( int s, int n ) {
    queue<int> Q;

    // INIt
    for ( int v = 1; v <= n; ++v ) {
        // 为了求1的闭环而不标记vis[1]
        if ( v == s ) {
            dis[ v ] = INF;
            vis[ v ] = false;
        } else if ( cost[ s ][ v ] != INF ) {
            dis[ v ] = cost[ s ][ v ];
            vis[ v ] = true;
            Q.push ( v );
        } else {
            dis[ v ] = INF;
            vis[ v ] = false;
        }
    }

    // spfa
    while ( !Q.empty () ) {
        int u = Q.front ();
        Q.pop ();
        vis[ u ] = false;

        for ( int v = 1; v <= n; ++v ) {

            if ( dis[ v ] > dis[ u ] + cost[ u ][ v ] ) {
                dis[ v ] = dis[ u ] + cost[ u ][ v ];
                if ( !vis[ v ] ) {
                    vis[ v ] = true;
                    Q.push ( v );
                }
            }
        }
    }
}

int main () {
    int n;
    while ( ~scanf ( "%d", &n ) ) {
        for ( int i = 1; i <= n; ++i )
            for ( int j = 1; j <= n; ++j )
                scanf ( "%d", &cost[ i ][ j ] );

        SPFA ( 1, n );
        int ans = dis[ n ];
        int loop = dis[ 1 ];

        SPFA ( n, n );
        loop += dis[ n ];

        ans = min ( ans, loop );
        printf ( "%d\n", ans );
    }
    return 0;
}

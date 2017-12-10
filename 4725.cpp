#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1000010;

int head[ MAXN ];

struct Node {
    int u, d;
    bool operator< ( const Node &rhs ) const { return d > rhs.d; }
};

struct Edge {
    int u, v, w, nex;
} edg[ MAXN ];

bool vis[ MAXN ];
int dis[ MAXN ];

void dijkstra ( int n, int s ) {
    memset ( vis, false, sizeof ( vis ) );
    for ( int i = 1; i <= n; ++i )
        dis[ i ] = INF;
    dis[ s ] = 0;

    priority_queue<Node> Q;
    Q.push ( Node{s, 0} );

    while ( !Q.empty () ) {
        Node x = Q.top ();
        Q.pop ();
        int u = x.u;

        if ( vis[ u ] )
            continue;
        vis[ u ] = true;

        for ( int i = head[ u ]; i != -1; i = edg[ i ].nex ) {
            int v = edg[ i ].v;
            int cost = edg[ i ].w;
            if ( !vis[ v ] && dis[ v ] > dis[ u ] + cost ) {
                dis[ v ] = dis[ u ] + cost;
                Q.push ( Node{v, dis[ v ]} );
            }
        }
    }
}

int cnt = 0;
void AddEdge ( int u, int v, int w ) {
    edg[ cnt ].u = u;
    edg[ cnt ].v = v;
    edg[ cnt ].w = w;
    edg[ cnt ].nex = head[ u ];
    head[ u ] = cnt;
    ++cnt;
}

int main () {
    int T;
    scanf ( "%d", &T );
    for ( int kse = 1; kse <= T; ++kse ) {

        memset ( head, -1, sizeof ( head ) );
        cnt = 0;

        int N, M, C;
        scanf ( "%d%d%d", &N, &M, &C );
        for ( int i = 1; i <= N; ++i ) {
            int lv;
            scanf ( "%d", &lv );
            //入点，出点
            AddEdge ( N + 2 * lv - 1, i, 0 );
            AddEdge ( i, N + 2 * lv, 0 );
        }

        for ( int i = 1; i < N; ++i ) {
            // x --> x+1 , x+1 --> x
            AddEdge ( N + 2 * i, N + 2 * ( i + 1 ) - 1, C );
            AddEdge ( N + 2 * ( i + 1 ), N + 2 * i - 1, C );
        }
        while ( M-- ) {
            int u, v, w;
            scanf ( "%d%d%d", &u, &v, &w );
            AddEdge ( u, v, w );
            AddEdge ( v, u, w );
        }

        dijkstra ( 3 * N, 1 );

        if ( dis[ N ] == INF )
            dis[ N ] = -1;
        printf ( "Case #%d: %d\n", kse, dis[ N ] );
    }

    return 0;
}

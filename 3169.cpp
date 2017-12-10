#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

#define N 10005
#define INF 0x3f3f3f3f

using namespace std;

struct Edge {
    int u, v, w, nex;
} edg[ N ];

int head[ N ];
int dis[ N ];
bool vis[ N ];

int c = 0;
void AddEdge ( int u, int v, int w ) {
    edg[ c ].u = u;
    edg[ c ].v = v;
    edg[ c ].w = w;
    edg[ c ].nex = head[ u ];
    head[ u ] = c;
    ++c;
}

int cnt[ N ];
bool SPFA ( int s, int n ) {
    memset ( cnt, 0, sizeof ( cnt ) );
    memset ( vis, false, sizeof ( vis ) );
    vis[ s ] = true;
    for ( int i = 1; i <= n; ++i )
        dis[ i ] = INF;
    dis[ 1 ] = 0;

    queue<int> Q;
    Q.push ( s );

    while ( !Q.empty () ) {
        int u = Q.front ();
        Q.pop ();
        vis[ u ] = false;

        for ( int i = head[ u ]; i != -1; i = edg[ i ].nex ) {
            int v = edg[ i ].v;
            int w = edg[ i ].w;

            if ( dis[ v ] > dis[ u ] + w ) {
                dis[ v ] = dis[ u ] + w;
                if ( !vis[ v ] ) {
                    Q.push ( v );
                    vis[ v ] = true;

                    if ( ++cnt[ v ] > n )
                        return false;
                }
            }
        }
    }
    return true;
}

int main () {

    c = 0;
    memset ( head, -1, sizeof ( head ) );

    int n, ml, md;
    scanf ( "%d%d%d", &n, &ml, &md );
    for ( int i = 0; i < ml; ++i ) {
        int a, b, d;
        scanf ( "%d%d%d", &a, &b, &d );
        AddEdge ( a, b, d );
    }

    for ( int i = 0; i < md; ++i ) {
        int a, b, d;
        scanf ( "%d%d%d", &a, &b, &d );
        AddEdge ( b, a, -d );
    }

    if ( !SPFA ( 1, n ) )
        printf ( "-1\n" );
    else if ( dis[ n ] == INF )
        printf ( "-2\n" );
    else
        printf ( "%d\n", dis[ n ] );

    return 0;
}

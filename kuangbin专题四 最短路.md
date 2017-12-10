### kuangbin专题四 最短路



ACM图论存图方式

http://jzqt.github.io/2015/07/21/ACM%E5%9B%BE%E8%AE%BA%E4%B9%8B%E5%AD%98%E5%9B%BE%E6%96%B9%E5%BC%8F/



### 单源最短路

####Dijkstra

​	$O(V^2+E)$

```cpp
int edg[ N ][ N ]; // weight of each edge
int dis[ N ];      // distance of each node from source
bool vis[ N ];     // SET S represent for nodes already visited

// CLRS 24.3
// s:start point,  n: total number of nodes
void dijkstra ( int s, int n ) {
    // INITIALIZE-SINGLE-SOURCE
    memset ( vis, false, sizeof ( vis ) );
    vis[ s ] = true;
    for ( int i = 1; i <= n; ++i )
        dis[ i ] = edg[ s ][ i ];
    dis[ s ] = 0;

    // Extract Min
    // u for the node, mi for dis[ u ]
    for ( int i = 1; i <= n - 1; ++i ) {
        int u = -1, mi = INF;
        for ( int j = 1; j <= n; ++j )
            if ( !vis[ j ] && dis[ j ] < mi )
                mi = dis[ u = j ];

        vis[ u ] = true;

        // Relax edges adjacent to u
        for ( int j = 1; j <= n; ++j )
            if ( !vis[ j ] )
                dis[ j ] = min ( dis[ j ], dis[ u ] + edg[ u ][ j ] );
    }
}
```

##### 



####Dijkstra + STL priority_queue

​	$O((V+E)lgV)$

```cpp
int head[ N ]; //链式前向星建图
int dis[ N ];  // distance of each node from source
bool vis[ N ]; // SET S represent for nodes already visited

struct Node {
    int u, d; // id, dis
    bool operator< ( const Node &rhs ) const { return d > rhs.d; }
};

struct Edge {
    int u, v, w, nex;
} edg[ N ];

// CLRS 24.3
// s:start point
void dijkstra ( int s ) {
    priority_queue<Node> Q;
    dis[ s ] = 0;
    Q.push ( ( Node ){s, dis[ s ]} );
    while ( !Q.empty () ) {
        // u = Extract_Min( Q )
        Node x = Q.top ();
        Q.pop ();
        int u = x.u;

        if ( vis[ u ] )
            continue;
        vis[ u ] = true;

        // for each vertex v in G.adj[ u ]
        for ( int i = head[ u ]; i != -1; i = edg[ i ].nex ) {
            int v = edg[ i ].v;
            int w = edg[ i ].w;
            // relax
            if ( dis[ v ] > dis[ u ] + w ) {
                dis[ v ] = dis[ u ] + w;
                Q.push ( ( Node ){v, dis[ v ]} );
            }
        }
    }
}
```



#### SPFA (Shortest Path Faster Algorithm)

​	$O(kE)$ ( k < 2 )

```cpp

int dis[ N ];  // distance of each node from source
bool vis[ N ]; // SET S represent for nodes already visited
int cnt[ N ];  //入列次数超过n，有负环
int head[ N ]; //链式前向星

struct edg {
    int u, v, w, nex;
} edg[ N ];

bool SPFA ( int s, int n ) {
    // INIT
    memset ( vis, false, sizeof ( vis ) );
    vis[ s ] = true;
    for ( int i = 1; i <= n; ++i )
        dis[ i ] = INF;
    dis[ s ] = 0;
    memset ( cnt, 0, sizeof ( cnt ) );
    cnt[ s ] = 1;

    // BFS方式的spfa
    queue<int> Q;
    Q.push ( s );

    while ( !Q.empty () ) {
        int u = Q.front ();
        Q.pop ();
        vis[ u ] = false; // 出队要取消标记

        for ( int i = head[ u ]; i != -1; i = edg[ i ].nex ) {
            int v = edg[ i ].v;
            // Relax所有出边
            if ( dis[ v ] > dis[ u ] + edg[ i ].w ) {
                dis[ v ] = dis[ u ] + edg[ i ].w;
                //没入队的标记并入队
                if ( !vis[ v ] ) {
                    vis[ v ] = true;
                    Q.push ( v );
                    // 判断负环
                    if ( ++cnt[ v ] > n )
                        return false;
                }
            }
        }
    }

    return true;
}
```



贴一个dfs的，自己没写过，感觉dijkstra+heap最好

```cpp
int spfa_dfs ( int u ) {
    vis[ u ] = true;
    for ( int i = head[ u ]; i != -1; i = edg[ i ].nex ) {
        int v = edg[ i ].v, w = edg[ i ].w;
        if ( dis[ u ] + w < dis[ v ] ) {
            dis[ v ] = dis[ u ] + w;
            if ( !vis[ v ] ) {
                if ( spfa_dfs ( v ) )
                    return 1;
            } else
                return 1;
        }
    }
    vis[ u ] = false;
    return 0;
}
```



#### Bellman-Ford

​	$O(VE)$

```cpp
int dis[ N ];  // distance of each node from source
bool vis[ N ]; // SET S represent for nodes already visited

struct edg {
    int u, v, w;
} edg[ N ];

//CLRS 24.1
//对每个点，relax所有的边
bool Bellman_Ford ( int n, int e, int s, double num ) {
    // Initialize Single Sorce( G,s )
    for ( int i = 1; i <= n; ++i )
        dis[ i ] = 0;
    dis[ s ] = num;

    // for i = 1 to |G.V|-1
    for ( int i = 0; i < n - 1; ++i ) {
        // for each edg ( u,v ) in G.E
        for ( int j = 0; j < e; ++j ) {
            int u = edg[ j ].u;
            int v = edg[ j ].v;
            // Relax
            if ( dis[ v ] > dis[ u ] + edg[ j ].w ) {
                dis[ v ] = dis[ u ] + edg[ u ].w;
            }
        }
    }
    // 存在负环
    for ( int i = 0; i < e; ++i )
        if ( dis[ edg[ i ].v ] > ( dis[ edg[ i ].u ] - edg[ i ].w ) )
            return false;
    return true;
}
```



#### 适用场景

如果是稠密图，Dijkstra+heap比SPFA快。稀疏图则SPFA更快。再就是SPFA可以判断负环



对于极端的链状图，SPFA无疑是最合适的了。每个结只进队一次，标准的O(E)。

朴素的dijkstra对于这样的图就力不从心了：每次循环都过一遍结点，在松弛，然后发现每次O(V)的时间只松弛了一个点。

​	

#### 多源最短路

#### Floyd

```cpp
// CLRS 25.2 All-Pairs-Shortest-Path
void Floyd () {
    // Dp
    // 表示所有点只经过集合{ 1..k }内的点时的最短路径
    // 只经过1的时候relax一次，在添加上经过2后的relax，最后一直到n
    for ( int k = 1; k <= n; ++k ) {
        //选取每一个起点
        for ( int i = 1; i <= n; ++i )
            //选取每一个终点
            for ( int j = 1; j <= n; ++j )
                // d(ij)^k = min { d(ik)^(k-1) + d(kj)^(k-1) }
                dis[ i ][ j ] = dis[ i ][ j ] || ( dis[ i ][ k ] && dis[ k ][ j ] );
    }
}

```





#### 题目列表

**A - Til the Cows Come Home POJ-2387 **

>一个农场有n (1000)个点，有t (2000)条道路连接,  从n到1最短

dijkstra 模板

**B - Frogger POJ-2253**

>无向图一条1~2的路径使得该路径上的最大边权最小. (max Route weight is the minimum among all routes)

dijkstra变形 double minimax = max ( mi, v\[ j \]\[ u \] );

**C - Heavy Transportation  POJ - 1797**

> 有n个城市，n个城市之间有m条公路或桥梁，每个公路或桥都有一个最大载重量，问从城市1到城市n所能运送到货物到最大重量是多少 ( min Route weight is the maximum among all routes )

dijkstra变形  int maxmini = min ( mi, v\[ j \]\[ u ] );

**D - Silver Cow Party POJ - 3268**

> n个农场，m条单向路，n个牛分别在n个农场，第x农场为终点，问每个牛从所在农场前往x农场的往返路程最小值是多少，求出n个牛中最短路上往返路程的最大的那个

从n个点到1再从1回到n个点，通过调转边的方向两次dijkstra

**E - Currency Exchange POJ - 1860**

>有n种货币，你含有num面额的其中一种货币。求有没有可能，在多次兑换后你手中的货币大于num。

求最大路径，反向用Bellman-Ford

**F - Wormholes POJ - 3259**

> 农场之间有很多条路，以及单向的虫洞，每条路走完会花费一定的时间，而虫洞可以回到之前的时间，问农场主是否能回到自己出发时间前的出发点

SPFA判断负环

**G - MPI Maelstrom POJ - 1502**

> 从第一个点出发，求到其他点最短路的最大值

dijkstra 注意下三角矩阵邻接表的建图

**H - Cow Contest POJ - 3660 **

>n个牛进行比赛，现已知m个关系， 牛u可以胜过牛v。问最后可以确定排名位数的有几个牛.

Floyd判断两两牛之间的关系。如果一个牛可以胜过a个牛，b个牛可以胜过它，那么如果a＋b＝n－1，他的排名就可以确定

**I - Arbitrage POJ - 2240 **

> 给定多种货币之间的兑换关系，问是否可以套利

Bellman-Ford判断正环（要返回自己所以松弛n次)

floyd判断回来后是否>1

**J - Invitation Cards POJ - 1511**

> 求源点到各点的往返最短路之和

邻接表逆置（建了两个邻接表）

数据多需要优化SPFA/dijkstra+heap

**K - Candies POJ - 3159 ** 

> 给n个人分糖果，m组数据a，b，c；意思是a比b少的糖果个数绝对不超过c个，也就是d(b)-d(a) < c，求1比n少的糖果数的最大值。

差分约束，和最短路的松弛一样

数据多，dijkstra+heap

**L - Subway POJ - 2502 **

> 小明步行的速度是10km/h，地铁速度是40km/h，给定家和学校的坐标，再给定多条地铁线路站点的坐标，问小明从家到学校所需的最短时间

dijkstra，建图连接所有的点并赋值时间

**M - 昂贵的聘礼 POJ - 1062**

>每个人可能有直接购买或者交换物品换取折扣这两种方式交易（交换物品要从别人手里买）
>
>等级差之间超过m的不能交易
>
>求用最少的钱买到非洲大酋长的承诺

等级限制采用枚举的方法，分别从lv[ 1 ] - m ~~ lv[ 1 ] + m，每次枚举的区间长度为m,一共m次最短路搜索

**N - Tram POJ - 1847** 

> 电动巴士在每个十字路口有一个默认方向，走向别的方向需要改动扳手。

dijkstra 每个边初始化为INF,要切换的路 = 1,不用切换 = 0

**O - Extended Traffic LightOJ - 1074**

> 给定每条街的拥挤度p(x)，街a到街b的时间就是(p(b)-p(a))**3，求第一个点到第k个点的最短路

SPFA判断负环

dfs记录负环里的点

**P - The Shortest Path in Nya Graph HDU - 4725**

>共n个点，n层(每个点单独一层)，相邻的两层之间权值为w 
>
>还有m条额外的边，权值为v，求1到n的最短路

建图 ！！给每个点两个辅助点，一个做出度，一个做入度

**Q - Marriage Match IV HDU - 3416 **

网络流，不会qwq

**R - 0 or 1 HDU - 4370 **

> X12+X13+...X1n=1,X1n+X2n+...Xn-1n=1,其余行列和相同，求ΣCij*Xij

神一样的建图！！节点1的出度为1.节点n的入度为1.节点2-n-1的入度和出度相等.

问题就相当于求一条最短路，从节点1出发，到节点N.

同时节点1的一个最小环+节点n的一个最小环也是可行解，两者取最小

**S - Layout POJ - 3169 **

> 两点间可能<= x 或者>=x，求1-->n最大

差分约束，和最短路一样，SPFA判断负环则代表不存在可行解
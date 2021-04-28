// C++ implementation of Hopcroft Karp algorithm for
// maximum matching
#include<bits/stdc++.h>
using namespace std;
#define NIL 0
#define INF INT_MAX
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,n,a) for (int i=n-1;i>=a;i--)
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
#define SZ(x) ((x).size())
#define i0(x) memset(x,0,sizeof(x))
#define i1(x) memset(x,-1,sizeof(x))
#define el cout<<endl
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define MOD 1000000007
#define N 100000
#define M 500000

#define trace1(x)                    cout <<#x<<": "<<x<< endl;
#define trace2(x, y)                 cout <<#x<<": "<<x<<" | "<<#y<<": "<<y<< endl;
#define trace3(x, y, z)              cout <<#x<<": "<<x<<" | "<<#y<<": "<<y<<" | "<<#z<<": "<<z<<endl;
#define trace4(a, b, c, d)           cout <<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl;

typedef long long ll;
typedef long double lld;

template<typename T, typename U> inline void amin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void amax(T &x, U y) { if(x < y) x = y; }
 int ismatched[1000001];
 set<ll> answer;
// A class to represent Bipartite graph for Hopcroft
// Karp implementation
class BipGraph
{
    // m and n are number of vertices on left
    // and right sides of Bipartite Graph
    int m, n;
 
    // adj[u] stores adjacents of left side
    // vertex 'u'. The value of u ranges from 1 to m.
    // 0 is used for dummy vertex
    list<int> *adj;
 
    // These are basically pointers to arrays needed
    // for hopcroftKarp()
    int *pairU, *pairV, *dist;
 
public:
    BipGraph(int m, int n); // Constructor
    void addEdge(int u, int v); // To add edge
    void fun(int temp1);
    // Returns true if there is an augmenting path
    bool bfs();
 
    // Adds augmenting path if there is one beginning
    // with u
    bool dfs(int u);
 
    // Returns size of maximum matcing
    int hopcroftKarp();
};
 
// Returns size of maximum matching
int BipGraph::hopcroftKarp()
{
    // pairU[u] stores pair of u in matching where u
    // is a vertex on left side of Bipartite Graph.
    // If u doesn't have any pair, then pairU[u] is NIL
    pairU = new int[m+1];
 
    // pairV[v] stores pair of v in matching. If v
    // doesn't have any pair, then pairU[v] is NIL
    pairV = new int[n+1];
 
    // dist[u] stores distance of left side vertices
    // dist[u] is one more than dist[u'] if u is next
    // to u'in augmenting path
    dist = new int[m+1];
 
    // Initialize NIL as pair of all vertices
    for (int u=0; u<=m; u++)
        pairU[u] = NIL;
    for (int v=0; v<=n; v++)
        pairV[v] = NIL;
 
    // Initialize result
    int result = 0;
 
    // Keep updating the result while there is an
    // augmenting path.
    while (bfs())
    {
        // Find a free vertex
        for (int u=1; u<=m; u++)
 
            // If current vertex is free and there is
            // an augmenting path from current vertex
            if (pairU[u]==NIL && dfs(u))
                result++;
    }
    return result;
}
 
// Returns true if there is an augmenting path, else returns
// false
bool BipGraph::bfs()
{
    queue<int> Q; //an integer queue
 
    // First layer of vertices (set distance as 0)
    for (int u=1; u<=m; u++)
    {
        // If this is a free vertex, add it to queue
        if (pairU[u]==NIL)
        {
            // u is not matched
            dist[u] = 0;
            Q.push(u);
        }
 
        // Else set distance as infinite so that this vertex
        // is considered next time
        else dist[u] = INF;
    }
 
    // Initialize distance to NIL as infinite
    dist[NIL] = INF;
 
    // Q is going to contain vertices of left side only. 
    while (!Q.empty())
    {
        // Dequeue a vertex
        int u = Q.front();
        Q.pop();
 
        // If this node is not NIL and can provide a shorter path to NIL
        if (dist[u] < dist[NIL])
        {
            // Get all adjacent vertices of the dequeued vertex u
            list<int>::iterator i;
            for (i=adj[u].begin(); i!=adj[u].end(); ++i)
            {
                int v = *i;
 
                // If pair of v is not considered so far
                // (v, pairV[V]) is not yet explored edge.
                if (dist[pairV[v]] == INF)
                {
                    // Consider the pair and add it to queue
                    dist[pairV[v]] = dist[u] + 1;
                    Q.push(pairV[v]);
                }
            }
        }
    }
 
    // If we could come back to NIL using alternating path of distinct
    // vertices then there is an augmenting path
    return (dist[NIL] != INF);
}
 
// Returns true if there is an augmenting path beginning with free vertex u
bool BipGraph::dfs(int u)
{
    if (u != NIL)
    {
        list<int>::iterator i;
        for (i=adj[u].begin(); i!=adj[u].end(); ++i)
        {
            // Adjacent to u
            int v = *i;
 
            // Follow the distances set by BFS
            if (dist[pairV[v]] == dist[u]+1)
            {
                // If dfs for pair of v also returns
                // true
                if (dfs(pairV[v]) == true)
                {
                    if(answer.find(pairU[u])!=answer.end())
                    answer.erase(answer.find(pairU[u]));
                    answer.insert(v);
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
 
        // If there is no augmenting path beginning with u.
        dist[u] = INF;
        return false;
    }
    return true;
}
 
// Constructor
BipGraph::BipGraph(int m, int n)
{
    this->m = m;
    this->n = n;
    adj = new list<int>[m+1];
}
 
// To add edge from u to v and v to u
void BipGraph::addEdge(int u, int v)
{
    adj[u].push_back(v); // Add u to v’s list.
}
void BipGraph::fun(int temp1)
{
    i0(ismatched);
    for(auto x : answer)
    {
        ismatched[x]=1;
    }
    fstream fio;
    fio.open("t_out1.txt",ios::trunc |  ios::out);
    fio<<temp1<<endl;
    fio.close();
}
void getinput()
{
    fstream fio;
    fio.open("t_bipartate.txt");
    string line;
    fio.seekg(0, ios::beg);
    getline(fio,line);
    int n,m;
    n=stoi(line);
    BipGraph g(n/2, n/2);
    getline(fio,line);
    m=stoi(line);
    rep(i,0,m)
    {
        getline(fio,line);
        int y[2];
        int cnt=0;
        istringstream ss(line);
        string x;
        while (ss >> x)
        y[cnt]=stoi(x),cnt++;
        g.addEdge(y[0],y[1]-n/2);
    //    v[y[1]].pb(y[0]);
      //  edge.pb(mp(y[0],y[1]));
    }
    int temp1=g.hopcroftKarp();
    //cout << "Size of maximum matching is " << temp1<<endl;
    g.fun(temp1);
    fio.close();
}
// Driver Program
int main()
{
    getinput();
    return 0;
}
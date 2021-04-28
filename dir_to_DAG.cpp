#include <bits/stdc++.h>
using namespace std;

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

ll powmod(ll a,ll b) {ll res=1;a%=MOD; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%MOD;a=a*a%MOD;}return res;}
ll n,m;
vector<ll> v[N],vr[N];
vector<ll> parent_list;   // WILL STORE THE LIST OF ALL PARENT NODES
vector<ll> scc[N];        // WILL SOTER ALL THE NODES IN SUPER NODES
vector<ll> v_scc[N];      // WILL STORE NEW GRAPH IN WHICH ONLY EDGE BETWEEN SAME COMPONENT WILL EXIST
ll vis[N];
map<ll,ll> mp1,mp2;
stack<ll> temp;
ll parent[N];
ll cnt[N];
void getinput()
{
    fstream fio;
    fio.open("t_directed1.txt");
    string line;
    fio.seekg(0, ios::beg);
    getline(fio,line);
    n=stoi(line);
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
        v[y[0]].pb(y[1]);
        vr[y[1]].pb(y[0]);
    }
    fio.close();
}
void dfs(ll cur,ll par)
{
    if(vis[cur]==1)
    return ;
    vis[cur]=1;
    for(auto x : v[cur])
    {
        if(x==par)
        continue;
        dfs(x,cur);
    }
    temp.push(cur);
}
void dfs1(ll cur,ll par,ll parent_node)
{
    if(vis[cur]==1)
    return ;
    vis[cur]=1;
    parent[cur]=parent_node;
    for(auto x : vr[cur])
    {
        dfs1(x,cur,parent_node);
    }
}
void strongly_connected()
{
    i0(vis);
    i0(parent);
    rep(i,1,n+1)
    {
        if(vis[i]==0)
        dfs(i,-1);
    }
    i0(vis);
    while(SZ(temp))
    {
        ll element=temp.top();
        temp.pop();
        if(vis[element]==1)
        continue;
        dfs1(element,-1,element);
        parent_list.pb(element);
    }
}
void print_graph()
{
    i0(cnt);
    set<pair<ll,ll> > s;
    rep(i,1,n+1)
    {
        for(auto x : v[i])
        {
            if(parent[i]!=parent[x])
            s.insert(mp(parent[i],parent[x]));
        }
    }
    fstream fio;
    fio.open("t_directed1.txt",ios::trunc |  ios::out );
    string line;
    fio.seekg(0, ios::beg);
    fio<<n<<endl;
    fio<<SZ(s)<<endl;
    for(auto x : s)
    {
        fio<<x.X<<" "<<x.Y<<endl;
    }
    fio.close();
}
void extra()
{
    rep(i,1,n+1)
    cout<<i<<" ";
    cout<<endl;
    rep(i,1,n+1)
    cout<<parent[i]<<" ";
    cout<<endl;
    rep(i,1,n+1)
    scc[parent[i]].pb(i);
    ll cnt=1;
    // MAPPINT FROM PARENT NODE TO NODE IN DAG
    for(auto x : parent_list)
    {
        mp1[x]=cnt;
        mp2[cnt]=x;
        cnt++;
    }
    //////////////////////////////////////////
    rep(i,1,n+1)
    {
        for(auto x : v[i])
        {
            if(parent[x]==parent[i])
            v_scc[i].pb(x);
        }
    }
}
void find_classification_for_all_SCCs()
{
    for(auto x : parent_list)
    {
        map<ll,ll> mp3,mp4;
        set<pair<ll,ll> > s;
        ll cnt=1;
        for(auto y : scc[x])
        {
            mp3[y]=cnt;
            mp4[cnt]=y;
            cnt++;
        }
        for(auto y : scc[x])
        {
            for(auto z : v_scc[y])
            s.insert(mp(mp3[y],mp3[z]));
        }
        fstream fio;
        fio.open("t_directed1.txt",ios::trunc |  ios::out );
        string line;
        fio.seekg(0, ios::beg);
        fio<<cnt-1<<endl;
        fio<<SZ(s)<<endl;
        for(auto x : s)
        fio<<x.X<<" "<<x.Y<<endl;
        fio.close();
        system("dir_to_bipartate1.exe");
        system("alternating_tree.exe");
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    getinput();
    strongly_connected();
    extra();
    //find_classification_for_all_SCCs();
    print_graph();
    return 0;
}
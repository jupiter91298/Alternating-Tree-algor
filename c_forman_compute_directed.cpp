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
vector<ll> v[10001];
lld formanvalue_node[10001];
lld formanvalue_node_in[10001];
lld formanvalue_node_out[10001];
int in_deg[10001]={0};
int out_deg[10001]={0};
map<pair<ll,ll> ,lld> formanvalue_edge;
map<pair<ll,ll>,ll > edge_vis;
ll n,m;
void getinput()
{
    fstream fio;
    fio.open("t_input.txt");
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
        out_deg[y[0]]++;
        in_deg[y[1]]++;
        v[y[0]].pb(y[1]);
    }
    fio.close();
}
void putoutput()
{
    fstream fio;
    fio.open("t_forman_value.txt",ios::trunc |  ios::out );
    string line;
    fio.seekg(0, ios::beg);
    rep(i,1,n+1)
    {
        fio<<abs(formanvalue_node[i])<<endl;
    }
    fio.close();
}
pair<ll,ll> getpair(ll x,ll y)
{
    return mp(x,y);
}
ll is_vis(ll x,ll y)
{
    if(edge_vis[getpair(x,y)]==1)
    return 1;
    return 0;
}
void mark_vis(ll x,ll y)
{
    edge_vis[getpair(x,y)]=1;
}
void compute_forman_curvature()
{
    rep(i,1,n+1)
    formanvalue_node[i]=0.0,formanvalue_node_in[i]=0.0,formanvalue_node_out[i]=0.0;
    rep(i,1,n+1)
    {
        for(auto x : v[i])
        {
            if(is_vis(i,x)==1)
            continue;
            mark_vis(i,x);
            lld temp=2.0;
            temp-=(in_deg[i]);
            temp-=(out_deg[x]);
            formanvalue_edge[getpair(i,x)]=temp;
            formanvalue_node_out[i]+=temp;
            formanvalue_node_in[x]+=temp;
            trace3(i,x,formanvalue_edge[getpair(i,x)])
        }
    }
    rep(i,1,n+1)
    {
        formanvalue_node[i]=formanvalue_node_in[i]-formanvalue_node_out[i];
        trace3(i,formanvalue_node_in[i],formanvalue_node_out[i])
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    getinput();
    /*rep(i,1,n+1)
    {
        cout<<i<<" :  ";
        for(auto x : v[i])
        cout<<x<<" ";
        cout<<endl;
    }*/
    compute_forman_curvature();
    rep(i,1,n+1)
    cout<<formanvalue_node[i]<<" ";
    cout<<endl;
    putoutput();
    return 0;
}
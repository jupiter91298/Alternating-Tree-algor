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
#define N 100001
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
ll parent[N];
vector<ll> v[N];   // GRAPH ADJ. LIST
ll label[N];
ll pred[N];
ll mate[N]={0};
ll n;
ll fun=0;
pair<ll,ll> bridge[N];
queue<ll> q;
ll cnt=0;
void augmenting_path(ll root,ll a,ll b);
ll find_base(ll root,ll a,ll b);
void shrink_path(ll lca,ll a,ll b);
void shrink_blossom(ll root,ll a,ll b);
void extend_tree(ll a,ll b);
void examine(ll root,ll a,ll b);
void alternating_tree(ll node);
void alternating_forest();
//   DSU
void make_set(ll v) {
    parent[v] = v;
}
ll find_set(ll v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
void union_sets(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}
void select(ll v)
{
    ll temp=find_set(v);
    parent[temp]=v;
    parent[v]=v;
}
// END OF DSU

void alternating_forest()
{
    fun=0;
    
    rep(i,1,n+1)
    label[i]=0,pred[i]=0,make_set(i);
    rep(i,1,n+1)
    {
        if(mate[i]==0)
        {
            fun=0;
            alternating_tree(i);
            cnt+=fun;
            if(fun==1)
            return ;
        }
    }
}
void alternating_tree(ll node)
{
    while(SZ(q))
    q.pop();
    q.push(node);
    label[node]=2;
    while(SZ(q))
    {
        ll cur_node=q.front();
        q.pop();
        for(auto x : v[cur_node])
        {
            examine(node,cur_node,x);
            if(fun==1)
            return ;
        }
    }
}
void examine(ll root,ll a,ll b)
{
    ll x=find_set(a);
    ll y=find_set(b);
    if(x!=y)
    {
        if(label[y]==0)
        {
            if(mate[b]==0)
            {
                augmenting_path(root,a,b);
                fun=1;
            }
            else
            extend_tree(a,b);
        }
        else if(label[y]==2)
        shrink_blossom(root,a,b);
    }
}
void extend_tree(ll a,ll b)
{
    label[b]=1;
    label[mate[b]]=2;
    pred[b]=a;
    pred[mate[b]]=b;
    q.push(mate[b]);
}
void shrink_blossom(ll root,ll a,ll b)
{
    trace3(root,a,b)
    ll lc=find_base(root,a,b);
    shrink_path(lc,a,b);
    shrink_path(lc,b,a);
}
void shrink_path(ll lca,ll a,ll b)
{
    ll u=find_set(a);
    while(lca!=u)
    {
        union_sets(lca,u);
        u=mate[u];
        union_sets(lca,u);
        select(lca);
        q.push(u);
        bridge[u]=mp(a,b);
        u=find_set(pred[u]);
    }
    cout<<"ok\n";
}
ll find_base(ll root,ll a,ll b)
{
    ll temp[n+1]={0};
    i0(temp);
    while(1)
    {
        temp[a]=1;
        if(a==root || a==0)
        break;
        a=pred[a];
    }
    while(1)
    {
        if(temp[b]==1)
        return b;
        b=pred[b];
    }
    return root;
}
void augmenting_path(ll root,ll a,ll b)
{
    ll temp1,temp2;
    pred[b]=a;
    label[b]=1;
    while(b!=0)
    {
        temp1=pred[b];
        temp2=mate[temp1];
        mate[temp1]=b;
        mate[b]=temp1;
        b=temp2;
    }
}
void readgraph()
{
    fstream fio;
    fio.open("t_input.txt");
    string line;
    fio.seekg(0, ios::beg);
    getline(fio,line);
    n=stoi(line);
    getline(fio,line);
    int m=stoi(line);
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
        v[y[1]].pb(y[0]);
    //    v[y[1]].pb(y[0]);
    }
    trace2(n,m)
    fio.close();
    return ;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    readgraph();
    alternating_forest();
    rep(i,1,n+1)
    cout<<i<<" "<<mate[i]<<endl;
    rep(i,1,n+1)
    trace2(i,pred[i])
    rep(i,1,n+1)
    trace2(i,find_set(i))
    trace1(cnt*2)
    return 0;
}
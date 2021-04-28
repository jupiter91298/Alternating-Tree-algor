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
vector<ll> v[10000001];
vector<pair<ll,ll> > edge;
ll max_match=0;
set<ll> s[10000001];
set<ll> ss[10000001];
ll cnt[10000000+1]={0};
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
        v[y[0]].pb(y[1]);
    //    v[y[1]].pb(y[0]);
        edge.pb(mp(y[0],y[1]));
    }
    trace2(n,m)
    fio.close();
}
void fun(ll mask)
{
    ll pos=1;
    rep(j,0,m)
    {
        if((mask&(1<<j))!=0)
        {
            if(s[mask].find(edge[j].Y)!=s[mask].end() || ss[mask].find(edge[j].X)!=ss[mask].end())
            pos=0;
            else
            s[mask].insert(edge[j].Y),ss[mask].insert(edge[j].X);
        }
    }
    if(pos==0)
    {
        s[mask].clear();
        return ;
    }
    amax(max_match,SZ(s[mask]));
}
void putoutput()
{
    fstream fio;
    fio.open("t_matched.txt",ios::trunc |  ios::out );
    string line;
    fio.seekg(0, ios::beg);
    cout<<"Mathed nodes are:\n";
    rep(i,1,n+1)
    {
        fio<<cnt[i]<<endl;
        if(cnt[i]!=0)
        trace1(i)
    }
    fio.close();
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    getinput();
    ll tot=(1<<m);
    rep(i,1,tot)
    fun(i);
    ll total=0;
    rep(i,1,tot)
    {
        if(SZ(s[i])==max_match)
        {
            for(auto x : s[i])
            cnt[x]++;
            total++;
        }
    }
    rep(i,1,n+1)
    trace2(i,cnt[i])
    trace1(max_match)
    i0(cnt);
    rep(i,1,tot+1)
    {
        if(SZ(s[i])==max_match)
        {
            for(auto x : s[i])
            cnt[x]++;
            break;
        }
    }
    putoutput();
    return 0;
}
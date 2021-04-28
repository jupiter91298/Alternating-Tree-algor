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
void read_and_convert()
{
    ll n,m;
    fstream fio,fio1;
    //fio.open("t_DAG.txt");
    fio.open("t_directed1.txt");
    fio1.open("t_bipartate.txt" ,ios::trunc |ios::out );
    string line;
    fio.seekg(0, ios::beg);
    fio1.seekg(0, ios::beg);
    getline(fio,line);
    n=stoi(line);
    getline(fio,line);
    m=stoi(line);
    fio1<<n*2<<endl;
    fio1<<m<<endl;
    rep(i,0,m)
    {
        getline(fio,line);
        int y[2];
        int cnt=0;
        istringstream ss(line);
        string x;
        while (ss >> x)
        y[cnt]=stoi(x),cnt++;
        fio1<<y[0]<<" " << y[1]+n<<endl;
    }
    fio1<<n<<endl;
    rep(i,1,n+1)
    fio1<<i<<endl;
    fio.close();
    fio1.close();
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    read_and_convert();
    return 0;
}
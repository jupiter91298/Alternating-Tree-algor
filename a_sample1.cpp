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
vector<ll> v[N];
void read_and_convert()
{
    fstream fio,fio1;
    //fio.open("t_DAG.txt");
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
    }
    fio.close();
}
void fun1()
{
    fstream fio4;
    fio4.open("DAG_output6.txt",ios::trunc |  ios::out);
    fio4.seekg(0,ios::beg);
    fio4<<"nodes = "<<n<<"  edges = "<<m<<endl;
    rep(i,1,n+1)
    {
        for(auto x : v[i])
        fio4<<i<<" "<<x<<endl;
    }
    fio4<<endl;
    rep(i,0,n+1)
    {
        ll cnt2=SZ(v[i]);
        rep(j,1,n+1)
        {
            for(auto x : v[j])
            {
                if(x==i)
                cnt2++;
            }
        }
        if(cnt2==0 && i!=0)
        continue;
        fio4<<"removed element = "<<i<<" :::     ";
        fio4<<"IN part unsaturated = ";
        fstream fio;
        fio.open("t_directed.txt",ios::trunc | ios::out);
        fio.seekg(0, ios::beg);
        fio<<n<<endl;
        set<pair<ll,ll>> s;
        rep(j,1,n+1)
        {
            for(auto x : v[j])
            {
                if(j==i || x==i)
                continue;
                s.insert(mp(j,x));
            }
        }
        fio<<SZ(s)<<endl;
        for(auto x : s)
        fio<<x.X<<" "<<x.Y<<endl;
        fio.close();


        system("dir_to_bipartate.exe");
        system("alternating_tree1.exe");
        
        fstream fio1;
        fio1.open("t_out2.txt");
        fio1.seekg(0, ios::beg);
        string line;
        getline(fio1,line);
        ll temp=stoi(line);
        rep(j,1,temp+1)
        {
            getline(fio1,line);
            if(stoi(line)==i)
            continue;
            fio4<<line<<" ";
        }
        fio1.close();
        fio4<<"  :::   OUT part unsaturated = ";

        fstream fio2,fio5;
        fio2.open("t_out1.txt");
        fio2.seekg(0, ios::beg);
        getline(fio2,line);
        temp=stoi(line);
        //trace1(temp)
        rep(j,1,temp+1)
        {
            getline(fio2,line);
            if(stoi(line)==i)
            continue;
            fio4<<line<<" ";
        }
        fio2.close();
        fio4<<endl;
        fio5.open("t_out3.txt");
        fio5.seekg(0, ios::beg);
        getline(fio5,line);
        temp=stoi(line);
        rep(j,1,temp+1)
        {
            getline(fio5,line);
            fio4<<line<<endl;
        }
        fio5.close();
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    system("dir_to_DAG.exe");
    read_and_convert();
    fun1();
    return 0;
}
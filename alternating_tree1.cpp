#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,n,a) for (int i=n-1;i>=a;i--)
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
#define SZ(x) ((x).size())
#define i0(x) memset(x,0,sizeof(x))
// #define i1(x) memset(x,-1,sizeof(x))
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

// BY CONVENTION I AM ALWAYS TAKING BIPARATE GRAPH WHICH IS 
// GENERATED FROM DIRECTED GRAPH

// FIRST N/2 NODES WILL BE V+ AND THE REST N/2 NODES WILL 
// BE V-

class BiGraph
{
    ll n,m;
    list<pair<ll,ll> > *v;
    ll *mate,*dist;
    ll **forest;
    ll **forest_edge_status;
    ll **forest_node_status;
    ll *ismatched;
    ll *is_in_same_tree;
    ll *is_present_in_alternating_tree;      // 1 IF IT DOES ELSE 0
    ll *is_present_in_alternating_tree_v_plus;
    list<ll> forest_root;        // GIVES THE LIST OF ALL NODES AT WHUCH TREE WAS CREATED(NOT ALL WILL HAVE UNMATCHED ROOT NODE)
    list<pair<ll,ll>> alternating_tree_roots;     // IT WILL STORE ALTERNATING TREE'S ROOT (WHICH WILL BE UNMATCHED NODES)
                                          // FIRST ITEM IN PAIR WILL STORE NODE IT SELF 
                                          // SECOND ITEM IN PAIR WILL STORE FOREST_NUMBER OF THIS TREE
                                          // ONE NOTE - IT WILL ALSO CONTAIN V+ NODES WHICH ARE NOT MATCHED SO BE ""CAREFUL""
                                          // FOR EXAMPLE IN FUNCTION compute_is_in_altranting_tree I HAD TO PUT "continue when x</n/2"
                                          // BECAUSE ALTERNATING TREE DOES NOT HAVE V+ AS ROOTS (BUT I AM COMPUTING LIKE THIS)
    list<pair<ll,ll> > edge;
    list<ll> classification1[3];
    list<ll> classification2[4][2];
    ll *rightorleft;
    public:
    BiGraph(ll x,ll y);
    void addEdge(ll x,ll y);
    void vertexPart(ll *a);
    void augment_path(ll x, ll y);
    int bfs(ll x,ll y);
    bool dfs(ll v);
    int alternating_tree();
    void info();
    void printAlternatingTreeRoots();
    void printDilation();
    void compute_classification1();
    void compute_classification2();
    void print_classification1();
    void print_classification2();
    void compute_is_present_in_alternating_tree();
    void compute_is_in_same_tree();
    void print_unmatched();
};
void BiGraph::print_unmatched()
{
    set<ll> temp1;
    rep(i,n/2+1,n+1)
    {
        if(mate[i]==-1)
        temp1.insert(i-n/2);
    }
    fstream fio2,fio3,fio4;
    fio2.open("t_out2.txt",ios::trunc |  ios::out);
    fio2<<SZ(temp1)<<endl;
    for(auto x : temp1)
    fio2<<x<<endl;
    fio2.close();

    temp1.clear();
    rep(i,1,n/2+1)
    {
        if(mate[i]==-1)
        temp1.insert(i);
    }
    fio3.open("t_out1.txt",ios::trunc |  ios::out);
    fio3<<SZ(temp1)<<endl;
    for(auto x : temp1)
    fio3<<x<<endl;
    fio3.close();
    fio4.open("t_out3.txt",ios::trunc |  ios::out);
    ll cnt1=0;
    rep(i,1,n/2+1)
    {
        ll matei=mate[i]-n/2;
        if(mate[i]!=-1)
        cnt1++;
    }
    fio4<<cnt1<<endl;
    rep(i,1,n/2+1)
    {
        ll matei=mate[i]-n/2;
        ll j=matei;
        if(mate[i]!=-1)
        fio4<<i<<" -> "<<j<<endl;
    }
}
void BiGraph::info()
{
    cout<<"TOTAL NODE = "<<n<<endl<<"TOTAL EDGE = "<<m<<endl;
    rep(i,1,n+1)
    {
        cout<<i<<" ::  ";
        for(auto x : v[i])
        cout<<x.X<<" ";
        cout<<endl;
    }
    rep(i,1,n+1)
    trace2(i,rightorleft[i])
    cout<<endl;
}
int BiGraph::alternating_tree()
{
    i0(is_present_in_alternating_tree);
    mate=new ll[n+1];
    rep(i,0,n+1)
    mate[i]=-1;
    ll count_forest=0;
    ll tot=0;
    rep(i,1,n+1)
    {
        //if(rightorleft[i]==2)
        //continue;
        if(mate[i]==-1)
        {
            int temp=bfs(i,count_forest);
            if(temp!=-1)
            augment_path(temp,count_forest),tot++;
            forest_root.push_back(i);
            if(temp==-1)
            alternating_tree_roots.push_back(mp(i,count_forest));
            count_forest++;
            /*cout<<"parent tree\n";
            rep(i,1,n+1)
            cout<<forest[count_forest-1][i]<<" ";
            cout<<endl;*/
        }
    }
    //cout<<"total matchign number = "<<tot<<endl;
    return tot;
}
void BiGraph::augment_path(ll element,ll forest_count)
{
    //trace1(element)
    while(element!=0)
    {
        ll temp=forest[forest_count][element];
        mate[temp]=element;
        mate[element]=temp;
        element=forest[forest_count][temp];
    }
}
int BiGraph::bfs(ll root,ll forest_count)
{
    //trace2(root, forest_count)
    queue<ll> q;
    q.push(root);
    forest[forest_count][root]=0;
    while(SZ(q))
    {
        ll cur_element=q.front();
        q.pop();
        for(auto x : v[cur_element])
        {
            if(mate[cur_element]==x.X)
            continue;
            if(forest[forest_count][x.X]!=-1)
            continue;
            forest[forest_count][x.X]=cur_element;
            if(mate[x.X]==-1)
            return x.X;
            q.push(mate[x.X]);
            forest[forest_count][mate[x.X]]=x.X;
        }
    }
    return -1;
}
void BiGraph::vertexPart(ll a[])
{
    rep(i,1,n+1)
    rightorleft[i]=a[i];
}
BiGraph::BiGraph(ll x,ll y)
{
    this->n=x;
    this->m=0;
    //trace2(x,y)
    v = new list<pair<ll,ll> >[n+1];
    forest = new ll*[n+1];
    forest_node_status = new ll*[n+1];
    forest_edge_status = new ll*[n+1];
    is_present_in_alternating_tree = new ll[n+1];
    is_present_in_alternating_tree_v_plus = new ll[n+1];
    rightorleft = new ll[n+1];
    ismatched = new ll[y+1];
    is_in_same_tree = new ll[n+1];
    rep(i,0,n+1)
    forest_edge_status[i]=new ll[y+1],forest[i]=new ll[n+1],forest_node_status[i]=new ll[n+1];
    rep(i,0,n+1)
    {
        rep(j,0,y+1)
        forest_edge_status[i][j]=-1;
        rep(j,0,n+1)
        forest_node_status[i][j]=-1,forest[i][j]=-1;
    }
}
void BiGraph::addEdge(ll x,ll y)
{
    v[x].pb(mp(y,m));
    v[y].pb(mp(x,m));
    edge.push_back(mp(x,y));
    m++;
}
void BiGraph::printAlternatingTreeRoots()
{
    for(auto x : alternating_tree_roots)
    cout<<x.X<<" ";
    cout<<endl;
}
void BiGraph::printDilation()
{
    // TO PRINT DILATION I AM FINDING ALL THE VERTICES WHICH ARE AT EVEN LEVEL IN THE TREE
    // BUT BY OUR CONVENTION ALL THE NODES V- WILL BE AT EVEN LEVEL AND SO FINDING ALL 
    // THE NODES WHICH HAS PARENT AND HAVE NUMBER(NODE NUMBER) GREATER THAN N/2 WIL BE
    // INCLUDEN IN THE DIALTION IN THAT PARTICULAR "ALTERNATING TREE"
    ll temp1=0;
    for(auto x : forest_root)
    {
        if(mate[x]==-1 && x>n/2)
        {
            cout<<"Dilation at root = "<<x-n/2<<"\n";
            rep(i,1,n+1)
            {
                if(forest[temp1][i]!=-1 && i>=n/2)
                cout<<i-n/2<<" ";
            }
            cout<<endl;
        }
        temp1++;
    }
    rep(i,1,n+1)
    trace2(i,mate[i])
}
void input()
{
    fstream fio;
    fio.open("t_bipartate.txt");
    string line;
    fio.seekg(0, ios::beg);
    getline(fio,line);
    int n,m;
    n=stoi(line);
    getline(fio,line);
    m=stoi(line);
    BiGraph g(n, m);
    rep(i,0,m)
    {
        getline(fio,line);
        int y[2];
        int cnt=0;
        istringstream ss(line);
        string x;
        while (ss >> x)
        y[cnt]=stoi(x),cnt++;
        g.addEdge(y[0],y[1]);
    //    v[y[1]].pb(y[0]);
      //  edge.pb(mp(y[0],y[1]));
    }
    getline(fio,line);
    ll temp=stoi(line);
    ll a[n+1]={0};
    rep(i,1,n+1)
    a[i]=2;
    rep(i,1,temp+1)
    {
        getline(fio,line);
        ll x=stoi(line);
        a[x]=1;
    }
    g.vertexPart(a);
    //g.info();
    ll temp1=g.alternating_tree();
    //cout << "Size of maximum matching is " << temp1<<endl;
    g.print_unmatched();
    
    /*g.compute_classification1();
    g.compute_classification2();
    g.printAlternatingTreeRoots();
    g.printDilation();
    g.print_classification1();
    g.print_classification2();*/
    fio.close();
}
void BiGraph::compute_classification1()
{
    /*
    Classification – 1
        1.      Vertices of degree zero in IN part of the bipartite graph
        2.      Vertices that belong to IN part and is at even level in the alternating tree
        3.      Vertices that belong to IN but not in any alternating tree
     WILL STORE ALL TYPES OF NODES IN CLASSIFICATION1 LIST 
     ALSO I AM STORING NODES V- WITH THEIR (NODE VALUE+NUMBER OF NODES) VALUE IN THE TREE
    */
    rep(i,n/2+1,n+1)
    {
        if(SZ(v[i])==0)
        classification1[0].pb(i);
    }
    // VERTICES WHICH BELONG TO V- WILL ALWAYS PRESENT AT EVEN LEVEL IN ALTERNATING TREE 
    // SO WILL STORE ALL THE V- NODES WHICH ARE PRESENT IN ALTERNATING TREE
    set<ll> temp_set;
    for(auto x : alternating_tree_roots)     // FIND NODES WHICH ARE PRESENT IN AN ALTERNTING TREE WHICH HAS V- AS ROOT NODE
    {
        if(x.X<=n/2 || SZ(v[x.X])==0)
        continue;
        rep(i,n/2+1,n+1)
        {
            if(forest[x.Y][i]!=-1)
            temp_set.insert(i);
        }
    }
    for(auto x : temp_set)
    classification1[1].pb(x);

    for(auto x : classification1[0])
    temp_set.insert(x);
    rep(i,n/2+1,n+1)
    {
        if(temp_set.find(i)==temp_set.end())
        classification1[2].pb(i);
    }
}
void BiGraph::compute_classification2()
{
    /*
    Classification – 2
        1.      V- belongs to case-1 of Classification-1 and
            a.      V+ is not present in any alternating tree
            b.      V+ is of degree zero or V= is at even level in the alternating tree
        2.      V- belongs to Case-3 of Classification-1 and
            a.      V+ is not present in any alternating tree
            b.      V+ is of degree zero or V= is at even level in the alternating tree
        3.      V- belongs to Case-2 of Classification-1 and the corresponding component does not contain a perfect matching
            a.      V+ is not present in any alternating tree
            b.      V+ is of degree zero or V= is at even level in the alternating tree
        4.      V- belongs to Case-2 of Classification-1 and the corresponding component does not contain a perfect matching
            a.      V+ and V- belong to the same component (i.e., are connected)
            b.      V+ and V- do not belong to the same component (i.e., are not connected)
    */
   // ALSO IN THIS CLASSIFICTION ALL THE NODES WILL BELONG TO V+
    compute_is_present_in_alternating_tree();
    for(auto x : classification1[0])
    {
        ll element=x-n/2;  // CORRESPONDING ELEMENT IN V+
        if(is_present_in_alternating_tree_v_plus[element]==0)
        classification2[0][0].pb(x);
        if(SZ(v[element])==0 || is_present_in_alternating_tree_v_plus[element]==1)
        classification2[0][1].pb(x);
    }

    for(auto x :classification1[2])
    {
        ll element=x-n/2;  // CORRESPONDING ELEMENT IN V+
        if(is_present_in_alternating_tree_v_plus[element]==0)
        classification2[1][0].pb(x);
        if(SZ(v[element])==0 || is_present_in_alternating_tree_v_plus[element]==1)
        classification2[1][1].pb(x);
    }
     
    for(auto x : classification1[1])
    {
        ll element=x-n/2;  // CORRESPONDING ELEMENT IN V+
        if(is_present_in_alternating_tree_v_plus[element]==0)
        classification2[2][0].pb(x);
        if(SZ(v[element])==0 || is_present_in_alternating_tree_v_plus[element]==1)
        classification2[2][1].pb(x);
    }
    compute_is_in_same_tree();
    for(auto x : classification1[1])
    {
        ll element=x-n/2;  // CORRESPONDING ELEMENT IN V+
        if(is_in_same_tree[x]==1)
        classification2[3][0].pb(x);
        else
        classification2[3][1].pb(x);
    }
}
void BiGraph::print_classification1()
{
    cout<<"Classification 1    ---- ALL THE NODES BELONG TO V-\n";
    rep(i,0,3)
    {
        cout<<i+1<<".\n==>";
        for(auto x : classification1[i])
        cout<<x-n/2<<" ";
        cout<<endl;
    }
}
void BiGraph::print_classification2()
{
    cout<<"CLASSIFICATION 2\n";
    rep(i,0,4)
    {
        cout<<i+1<<"."<<endl;
        rep(j,0,2)
        {
            cout<<"\t"<<char('a'+j)<<".\n"<<"\t==>  ";
            for(auto x : classification2[i][j])
            cout<<x-n/2<<" ";
            cout<<endl;
        }
    }
}
void BiGraph::compute_is_present_in_alternating_tree()
{
    //  is_present_in_altenating_tree WILL CHECK IS NODE IS PRESENT IN AN ALTERNATING TREE WHICH HAS ROOT FROM V-
    // is_presetn_in_any_alteranting_tree WILL CHECK IF NODE IS PRESENT IN ANY ALTERNATING TREE
    rep(i,0,n+1)
    is_present_in_alternating_tree[i]=0,is_present_in_alternating_tree_v_plus[i]=0;
    for(auto x : alternating_tree_roots)
    {
        if(x.X<=n/2)
        continue;
        rep(i,1,n+1)
        {
            if(forest[x.Y][i]!=-1)
            is_present_in_alternating_tree[i]=1;
        }
    }
    for(auto x : alternating_tree_roots)
    {
        if(x.X>n/2)
        continue;
        rep(i,1,n+1)
        {
            if(forest[x.Y][i]!=-1)
            is_present_in_alternating_tree_v_plus[i]=1;
        }
    }
}
void BiGraph::compute_is_in_same_tree()
{
    i0(is_in_same_tree);
    ll vis[n+1]={0};
    rep(i,1,n+1)
    {
        queue<ll> temp;
        set<ll> s;
        if(vis[i]==0)
        {
            temp.push(i);
            while(SZ(temp)!=0)
            {
                ll element=temp.front();
                s.insert(element);
                temp.pop();
                if(vis[element]==1)
                continue;
                vis[element]=1;
                for(auto x : v[element])
                {
                    if(vis[x.X]==0)
                    temp.push(x.X);
                }
            }
        }
        for(auto x : s)
        {
            if(x<=n/2)
            continue;
            if(s.find(x-n/2)!=s.end())
            is_in_same_tree[x]=1,is_in_same_tree[x-n/2]=1;
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    input();
    return 0;
}
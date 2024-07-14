#include<bits/stdc++.h>
using namespace std;
#define int long long int
unordered_map<int,int>m_child;
unordered_map<int,char>m_char;
unordered_map<int,int>postorder;
string s;
int node_count;
class manacher{
public:
    vector<int>p;
    void run_manacher(string s){
        int n=s.size();
        p.assign(n,1);
        int l=1,r=1;
        for(int i=1;i<n;i++){
            p[i]=max((int)0,min(r-i,p[l+r-i]));
            while(i-p[i]>=0 and i+p[i]<n and s[i-p[i]]==s[i+p[i]]){
                p[i]++;
            }
            if(i+p[i]>r){
                l=i-p[i];
                r=i+p[i];
            }
        }
    }
    manacher(string s){
        string t="";
        for(int i=0;i<s.size();i++){
            t+='*';
            t+=s[i];
        }
        t+='*';
        run_manacher(t);
    }
    int getLongest(int cen,int odd){
        int pos=2*cen+1+(!odd);
        return p[pos]-1;
    }
    int checkPalindrome(int l,int r){
        if((r-l+1)<=getLongest((l+r)/2,l%2==r%2)) return 1;
        return 0;
    }
};
int dfs(int node,vector<int>&vis,vector<set<int>>&v){
    vis[node]=1;
    int count=1;
    for(auto w:v[node]){
        if(!vis[w]) count+=dfs(w,vis,v);
    }
    s+=m_char[node];
    m_child[node]=count;
    postorder[node]=node_count++;
    return count;
}
void solve(){
    int n; cin>>n;
    vector<set<int>>v(n+1);
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        v[a].insert(b);
        v[b].insert(a);
    }
    for(int i=1;i<=n;i++){
        char c; cin>>c;
        m_char[i]=c;
    }
    s="";
    node_count=0;
    vector<int>vis(n+1,0);
    dfs(1,vis,v);
    manacher k(s);
    int query;
    cin>>query;
    while(query--){
        int node;
        cin>>node;
        int rindex=postorder[node];
        int lindex=postorder[node]-m_child[node]+1;
        cout<<k.checkPalindrome(lindex,rindex)<<endl;
    }
    return ;
}
int32_t main(){
    int t=1;
    while(t--){
        solve();
    }
    return 0;
}

/*
每个结点
struct node{
    int l,r,d,u;
    int sum;//要维护的结点的信息；
    int ch[4];//四个小矩阵的标号；
}T[Maxn];
更新基本同一维线段树，
void update(int l,int r,int d,int u,int rt,int v){
    if (l<=T[rt].l && T[rt].r<=r && d<=T[rt].d && T[rt].u<=u){
        T[rt].sum+=v;
        return;
    }
};
int query(int l,int r,int d,int u,int rt){
    if (l<=T[rt].l && T[rt].r<=r && d<=T[rt].d && T[rt].u<=u){
        return T[rt].sum;
    }
};
为了节省空间，只对用到的结点申请内存；

*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<bitset>
#include<string>
#include<cmath>
using namespace std;
const int N=20000*15;
struct node{
    int l,r,d,u,sum;
    int ch[4];
    node(){}
    node(int a,int b,int c,int e,int f):l(a),r(b),d(c),u(e),sum(f){}
}T[N];

int idx;
int Newnode(int l,int r,int d,int u){
    idx++;
    T[idx]=node(l,r,d,u,0);
    memset(T[idx].ch,0,sizeof(T[idx].ch));
    return idx;
}
void update(int x,int y,int rt,int v){
    if (T[rt].l==T[rt].r && T[rt].u==T[rt].d){
        T[rt].sum+=v;
        return;
    }
    int m1=(T[rt].l+T[rt].r)>>1;
    int m2=(T[rt].u+T[rt].d)>>1;
    if (x<=m1 && y<=m2){//左下
        if (T[rt].ch[0]==0){
            T[rt].ch[0]=Newnode(T[rt].l,m1,T[rt].d,m2);
        }
        update(x,y,T[rt].ch[0],v);
    }
    if (x<=m1 && y>m2){//左上
        if (T[rt].ch[1]==0){
            T[rt].ch[1]=Newnode(T[rt].l,m1,m2+1,T[rt].u);
        }
        update(x,y,T[rt].ch[1],v);
    }
    if (x>m1 && y<=m2){//右下
        if (T[rt].ch[2]==0){
            T[rt].ch[2]=Newnode(m1+1,T[rt].r,T[rt].d,m2);
        }
        update(x,y,T[rt].ch[2],v);
    }
    if (x>m1 && y>m2){//右上
        if (T[rt].ch[3]==0){
            T[rt].ch[3]=Newnode(m1+1,T[rt].r,m2+1,T[rt].u);
        }
        update(x,y,T[rt].ch[3],v);
    }
    T[rt].sum=0;//合并
    for (int i=0;i<4;i++){
        int c=T[rt].ch[i];
        T[rt].sum+=T[c].sum;
    }
}
int query(int l,int r,int d,int u,int rt){
    if (l<=T[rt].l && T[rt].r<=r && d<=T[rt].d && T[rt].u<=u){
        return T[rt].sum;
    }
    int m1=(T[rt].l+T[rt].r)>>1;
    int m2=(T[rt].u+T[rt].d)>>1;
    int ret=0;
    if (l<=m1 && d<=m2){
        if (T[rt].ch[0]!=0){
            ret+=query(l,r,d,u,T[rt].ch[0]);
        }
    }
    if (l<=m1 && m2<u){
        if (T[rt].ch[1]!=0){
            ret+=query(l,r,d,u,T[rt].ch[1]);
        }
    }
    if (m1< r && d<=m2){
        if (T[rt].ch[2]!=0){
            ret+=query(l,r,d,u,T[rt].ch[2]);
        }
    }
    if (m1< r && m2< u){
        if (T[rt].ch[3]!=0){
            ret+=query(l,r,d,u,T[rt].ch[3]);
        }
    }
    return ret;
}
char s[100];
int main(){
    int flag=0;
    while (gets(s)){
        idx=0;
        Newnode(1,20000,1,20000);
        while (1){
            if (s[0]=='I'){
                flag=1;
            }else
            if (s[0]=='Q'){
                flag=2;
            }else
            if (s[0]=='E') break;
            else if (s[0]>='0' && s[0]<='9'){
                int x1,x2,y1,y2,v;
                if (flag==1){
                    sscanf(s,"%d%d%d",&x1,&y1,&v);
                //    cout<<"** "<<x1<<" "<<y1<<" "<<v<<endl;
                    update(x1,y1,1,v);
                //    cout<<"++++ "<<T[1].sum<<endl;
                }else if (flag==2){
                    sscanf(s,"%d%d%d%d",&x1,&x2,&y1,&y2);
                    //cout<<"/// "<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<endl;
                    printf("%d\n",query(x1,x2,y1,y2,1));
                }
            }
            gets(s);
        }
    }
    return 0;
}

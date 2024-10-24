
using pii=pair<int,int>;
int kx[sz],mu[sz];

/*
Ex)
int S(pii x){
    int ret=0;
    kx[0]=0;
    for(int i=1;i<=n;i++)kx[i]=kx[i-1]+i*x.first/x.second;
    for(int i=1;i<=n;i++){
        ret+=mu[i]*kx[n/i];
    }
    return ret;
}
*/

int expSearch(pii L,pii R,const auto &g){
    if(!g(L,R,1))return 0;
    int l=1,r=2,mid;
    while(g(L,R,r)){
        l<<=1;
        r<<=1;
    }
    while(l+1<r){
        mid=(l+r)>>1;
        if(g(L,R,mid))l=mid;
        else r=mid;
    }
    return l;
}

bool f(pii x){
  return false;
}

pii SternBrocotBS(){
    pii L(0,1),R(1,0);
    auto chkL=[](pii L,pii R,int x){
        return L.second*x + R.second <= n && !f(pii(L.first*x + R.first, L.second*x + R.second));
    };
    auto chkR=[](pii L,pii R,int x){
        return L.second + R.second*x <= n && f(pii(L.first + R.first*x, L.second + R.second*x));
    };
    while(1){
        int x=expSearch(L, R, chkL);
        if(x)R=pii(L.first*x+R.first,L.second*x+R.second);
        
        int y=expSearch(L,R,chkR);
        if(y)L=pii(L.first+R.first*y,L.second+R.second*y);
        if(!x&&!y)break;
    }
    return L;
}

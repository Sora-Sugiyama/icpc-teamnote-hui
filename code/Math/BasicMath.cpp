// ll gcd(ll a, ll b), ll lcm(ll a, ll b), ll mod(ll a, ll b)
ll ext_gcd(ll a, ll b, ll &x, ll &y) { //ax + by = gcd(a, b)
  ll g = a; x = 1, y = 0;
  if (b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
  return g;
}
ll inv(ll a, ll m){ //return x when (ax mod m = 1), fail -> -1
  ll x, y, g = ext_gcd(a, m, x, y);
  if(g > 1) return -1;
  return mod(x, m);
}
pair<ll,ll> crt(ll a1, ll m1, ll a2, ll m2){ // Return (z, M), fail -> M = -1
  ll s, t; ll g = ext_gcd(m1, m2, s, t);
  if(a1 % g != a2 % g) return {0, -1};
  s = mod(s*a2, m2); t = mod(t*a1, m1);
  ll res = mod(s*(m1/g) + t*(m2/g), m1/g*m2), M = m1/g*m2;
  return {res, M};
}
pair<ll,ll> crt(const vector<ll> &a, const vector<ll> &m){
  if(a.size() == 1) return {a[0], m[0]};
  pair<ll,ll> ret = crt(a[0], m[0], a[1], m[1]);
  for(int i=2; i<a.size(); i++) ret = crt(ret.x, ret.y, a[i], m[i]);
  return ret;
}
struct Lucas{ // init : O(P), query : O(log P)
  const size_t P;
  vector<ll> fac, inv;
  ll Pow(ll a, ll b){
    ll ret = 1;
    for(; b; b>>=1, a=a*a%P) if(b&1) ret=ret*a%P;
    return ret;
  }
Lucas(size_t P) : P(P), fac(P), inv(P) {
    fac[0] = 1;
    for(int i=1; i<P; i++) fac[i] = fac[i-1] * i % P;
    inv[P-1] = Pow(fac[P-1], P-2);
    for(int i=P-2; ~i; i--) inv[i] = inv[i+1] * (i+1) % P;
  }
  ll small(ll n, ll r) const {
    if(n < r) return 0;
    return fac[n] * inv[r] % P * inv[n-r] % P;
  }
  ll calc(ll n, ll r) const {
    if(n < r || n < 0 || r < 0) return 0;
    if(!n || !r || n == r) return 1;
    return small(n%P, r%P) * calc(n/P, r/P) % P;
  }
};
template<ll p, ll e> struct CombinationPrimePower{ // init : O(p^e), query : O(log p)
  vector<ll> val; ll m;
  CombinationPrimePower(){
    val.resize(m); val[0] = 1; m = 1; for(int i=0; i<e; i++) m *= p;
    for(int i=1; i<m; i++) val[i] = val[i-1] * (i % p ? i : 1) % m;
  }
  pair<ll,ll> factorial(int n){
    if(n < p) return {0, val[n]};
    int k = n / p; auto v = factorial(k);
    int cnt = v.first + k, kp = n / m, rp = n % m;
    ll ret = v.second * Pow(val[m-1], kp % 2, m) % m * val[rp] % m;
    return {cnt, ret};
  }
  ll calc(int n, int r){
    if(n < 0 || r < 0 || n < r) return 0;
    auto v1 = factorial(n), v2 = factorial(r), v3 = factorial(n-r);
    ll cnt = v1.first - v2.first - v3.first;
    ll ret = v1.second * inv(v2.second, m) % m * inv(v3.second, m) % m;
    if(cnt >= e) return 0;
    for(int i=1; i<=cnt; i++) ret = ret * p % m;
    return ret;
  }
};
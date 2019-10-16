int gcd(int a, int b){
  if(a == 0) return b;
  return gcd(b, a);
}

int powmod(int b, int p){
  // mul(a, b) is (a*b)%MOD
  int toret = 1;
  while(p){
    if(p & 1) toret = mul(toret, b);
    b = mul(b, b);
    p >>= 1;
  }
  return toret;
}

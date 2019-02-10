int min(int a, int b){
  return a < b ? a : b;
}

int max(int a, int b){
  return a > b ? a : b;
}

int gcd(int a, int b){
  if(a == 0) return b;
  return gcd(b, a);
}

int sieve[1000006];
void get_primes(void){
  int i;
  sieve[0] = -1;
  sieve[1] = -1;
  for(i = 0; i < 1000006;i++)if(sieve[i] != -1){
      int j;
      for(j = 2 * i; j < 1000006; j += i){
	sieve[j] = -1;
      }
  }
}

#define MOD 1000000007

int add(int a, int b){
  a += b;
  if(a >= MOD) a -= MOD;
  return a;
}

int mul(int a, int b){
  return (a * 1ll * b)%MOD;
}

int powmod(int b, int p){
  int toret = 1;
  while(p){
    if(p & 1) toret = mul(toret, b);
    b = mul(b, b);
    p >>= 1;
  }
  return toret;
}

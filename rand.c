// constant values from http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/CODES/mt19937ar.c
// returns unsigned instead of signed int; bit-shifts work differently for signed and unsigned

unsigned int mt19937_arr[624];
int mt19937_idx = 625;

void mt19937_seed(int seed){
  int i;
  unsigned int *arr;
  arr = mt19937_arr;
  arr[0] = seed;
  for(i = 1; i < 624;i++) arr[i] = 1812433253 * (arr[i - 1] ^ (arr[i - 1] >> 30)) + i;
  mt19937_idx = 624;
}

unsigned mt19937_rand(void){
  unsigned int y, *arr, umask, lmask, mat[2];
  
  arr = mt19937_arr;
  umask = (1 << 31);
  lmask = ~(1 << 31);
  mat[0] = 0;
  mat[1] = 2567483615;
  
  if(mt19937_idx >= 624){
    int i;
    
    if(mt19937_idx > 624){
      mt19937_seed(142857);
    }

    for(i = 0;i < 227;i++){
      y = (arr[i] & umask) | (arr[i + 1] & lmask);
      arr[i] = arr[i + 397] ^ (y >> 1) ^ mat[y&1];
    }
    for(;i < 623;i++){
      y = (arr[i] & umask) | (arr[i + 1] & lmask);
      arr[i] = arr[i - 227] ^ (y >> 1) ^ mat[y&1];
    }

    y = (arr[623] & umask) | (arr[0] & lmask);
    arr[623] = arr[396] ^ (y >> 1) ^ mat[y&1];

    mt19937_idx = 0;
  }

  y = arr[mt19937_idx++];
  y ^= (y >> 11);
  y ^= (y << 7) & 2636928640;
  y ^= (y << 15) & 4022730752;
  y ^= (y >> 18);

  return y;
}

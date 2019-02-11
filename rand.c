// PCGs from https://nullprogram.com/blog/2017/09/21/
// Make sure it is seeded before generating rand()s

unsigned int pcg32_rand(void);
unsigned long long pcg32_arr[2];

unsigned int pcg32_rand(void){
  unsigned long long prev, xorshift, rot;
  prev = pcg32_arr[0];
  pcg32_arr[0] = prev * 6364136223846793005 + pcg32_arr[1];
  xorshift = ((prev >> 18) ^ prev) >> 27;
  rot = prev >> 59;
  return (xorshift >> rot) | (xorshift << ((-rot) & 31));
}

void pcg32_seed(unsigned long long seed){
  pcg32_arr[0] = 0;
  pcg32_arr[1] = ((unsigned long long)0xca77123abcda1773 << 1) | 1; // MUST be odd
  pcg32_rand();
  pcg32_arr[0] += seed;
  pcg32_rand();
}

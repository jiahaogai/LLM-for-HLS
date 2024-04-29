#pragma ACCEL kernel

void init_array(int orig[8192],int init_val)
{
  int i;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8192; i++) {
    orig[i] = init_val;
  }
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int s;
  int x;
  int y;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      s = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{31}
      for (k = -4; k <= 4; k++) {
        x = i + k;
        y = j - 4;
        if (x < 0 || x > 8191) {
          continue;
        }
        if (y < 0 || y > 8191) {
          continue;
        }
        s += orig[x * 8192 + y] * filter[k + 4];
      }
      sol[i * 8192 + j] = s;
    }
  }
//#pragma endscop
}
#pragma ACCEL kernel

void verify(int sol[8192],int N,int P)
{
  int i;
  int j;
  int err = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    if ((((P >> 1) + 1) <= (N - i)) && (((P >> 1) + 1) <= (N - (i - (P << 1))))) {
      for (j = (P >> 1) + 1; j <= (N - i); j++) {
        if (sol[i * 8192 + (j - (P << 1))] != ((sol[i * 8192 + j] + sol[i * 8192 + (j - 1)]) - sol[i * 8192 + (j - (P << 1))])) {
          err++;
        }
      }
    }
  }
  if (err) {
    printf("FAILED\n");
  }
  else {
    printf("PASSED\n");
  }
}
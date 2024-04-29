#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4; k <= 4; k++) {
        int idx = (i - 1) * 8192 + j + k;
        if (idx < 0) {
          idx = 0;
        }
        if (idx > 8191) {
          idx = 8191;
        }
        t += filter[k + 4] * orig[idx];
      }
      sol[i * 8192 + j] = t;
    }
  }
//#pragma endscop
}
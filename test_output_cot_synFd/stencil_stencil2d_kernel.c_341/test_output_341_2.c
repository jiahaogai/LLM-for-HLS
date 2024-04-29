#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int jj;
  int ii;
  int r;
  int q;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    int sum = 0.0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    inner:
    for (j = 0; j < 9; j++) {
      jj = i - 4 + j;
      if (jj < 0) {
        jj = 0;
      }
      if (jj > 8191) {
        jj = 8191;
      }
      sum += filter[j] * orig[jj];
    }
    sol[i] = sum;
  }
}
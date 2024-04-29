#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int jj;
  int idx;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 1; k < 32 + 1 - 1; k++) {
      sum = 0.0;
      loopjj:
      for (jj = -1; jj < 0 + 1 + 1; jj++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        loopidx:
        for (idx = -1; idx < 0 + 1 + 1; idx++) {
          sum += filter[jj + 1] * orig[idx + 32 * (j + k)];
        }
      }
      sol[32 * (j + 1 - 1) + k - 1] = sum;
    }
  }
}
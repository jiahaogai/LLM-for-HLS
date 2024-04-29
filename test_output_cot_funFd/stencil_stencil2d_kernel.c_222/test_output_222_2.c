#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      s = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      for (k = -4; k <= 4; k++) {
        idx = (i + k) * 8192 + j;
        if (idx < 0) {
          idx = -idx;
        }
        else {
          if (idx >= 8192) {
            idx = 8192 * 2 - idx;
          }
        }
        s += orig[idx] * filter[k + 4];
      }
      sol[i * 8192 + j] = s;
    }
  }
}
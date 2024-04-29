#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 1; j < 8191; j++) {
      t = 0;
      idx = 4 * (i - 1) * (8192) + 4 * (j - 1);
      for (k = 0; k < 9; k++) {
        s = idx + 4 * (k - 1);
        t += filter[k] * orig[s];
      }
      sol[idx + 4] = t;
    }
  }
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = (i - 1) * 8191 + j - 1;
      val = orig[idx] * filter[0];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 1; k < 9; k++) {
        val += orig[idx + k - 1] * filter[k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 1; k < 9; k++) {
        val += orig[idx - k + 1] * filter[k];
      }
      sol[idx] = val;
    }
  }
}
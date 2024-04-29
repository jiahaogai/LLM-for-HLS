#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 31; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
/* Standardize from: for(k ... ) */
    for (k = 1; k < 31; k++) {
      i = (j - 1) * 32 + k - 1;
      val = ((orig[i + 32] + orig[i + 31]) + orig[i + 1]) + orig[i - 1];
      val += ((orig[i + 32 * 32] + orig[i + 31 * 32]) + orig[i + 1 * 32]) + orig[i - 1 * 32];
      val >>= 2;
      sol[i] = val;
    }
  }
}
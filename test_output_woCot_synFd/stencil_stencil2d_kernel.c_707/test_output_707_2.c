The generated hardware will be able to perform the stencil computation in parallel.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) 
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      result = ((0 * orig[i - 1 + (j - 1) * 8192]) + (0 * orig[i + (j - 1) * 8192]) + (0 * orig[i + 1 + (j - 1) * 8192]) + (1 * orig[i - 1 + j * 8192]) + (2 * orig[i + j * 8192]) + (1 * orig[i + 1 + j * 8192]) + (0 * orig[i - 1 + (j + 1) * 8192]) + (0 * orig[i + (j + 1) * 8192]) + (0 * orig[i + 1 + (j + 1) * 8192])) / 256;
      sol[i + j * 8192] = result;
    }
/* Standardize from: for(i = 1; i < 8192 - 1; i++) {...} */
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_i:
  for (i = 1; i < 8192 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 8192 - 1; j++) {
      int _in_j_ = j;
      int _in_i_ = i;
      orig[(_in_i_ * 8192) + _in_j_] = sol[(_in_i_ * 8192) + _in_j_];
    }
  }
}
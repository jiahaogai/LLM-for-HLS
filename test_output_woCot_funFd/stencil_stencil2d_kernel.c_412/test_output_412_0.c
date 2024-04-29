#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8188; j++) {
      result = ((orig[i * 8192 + j] + orig[i * 8192 + j + 1] + orig[i * 8192 + j + 8192] + orig[i * 8192 + j + 8193]) + (orig[i * 8192 + j + 8192 * 2] + orig[i * 8192 + j + 8192 * 2 + 1] + orig[i * 8192 + j + 8192 * 2 + 8192] + orig[i * 8192 + j + 8192 * 2 + 8193])) + (orig[i * 8192 + j + 8192 * 3] + orig[i * 8192 + j + 8192 * 3 + 1] + orig[i * 8192 + j + 8192 * 3 + 8192] + orig[i * 8192 + j + 8192 * 3 + 8193]);
      sol[i * 8192 + j] = result;
    }
  }
/* Standardize from: for(i = 1...8190) {...} to: */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  i = 1 + 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  while (i < 8190 + 0) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    j = 1 + 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (j < 8188 + 0) {
      ((sol[i * 8192 + j] < 1) ? (sol[i * 8192 + j] = 0) : ((sol[i * 8192 + j] > 2) ? (sol[i * 8192 + j] = 2) : (sol[i * 8192 + j] = 1)));
      j++;
    }
    i++;
  }
/* Standardize from: for(i = 1...8190) {...} to: */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  i = 1 + 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (i < 8190 + 0) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    j = 1 + 0;
    
#pragma ACCEL PARALLEL FACT
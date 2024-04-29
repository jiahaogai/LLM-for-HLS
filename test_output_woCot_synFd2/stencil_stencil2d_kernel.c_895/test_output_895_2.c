#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int oidx;
  int sum;
  int flatten_id_0;
  int flatten_id_1;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_flatten_0:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
  for (i = 1 + 1; i < 32 + 1 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_flatten_1:
/* Standardize from: for(j = 1; j < 32 + 1 - 1; j++) {...} */
    for (j = 1 + 1; j < 32 + 1 - 1; j++) {
      idx = i * 32 + j;
      sum = 0.0;
      loop_flatten_2:
/* Standardize from: for(k = 0; k < 9; k++) {...} */
      for (k = 0; k < 9; k++) {
        oidx = idx - 1 + k;
        sum += ((double )filter[k]) * orig[oidx];
      }
      sol[idx] = sum;
    }
  }
}
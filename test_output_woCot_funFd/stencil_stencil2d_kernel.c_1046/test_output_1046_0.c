#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int min_i;
  int max_i;
  int min_j;
  int max_j;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_j:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j < 8192 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_i:
    for (i = 1; i < 8192 - 1; i++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{6}
      loop_t:
      for (t = 0; t < 9; t++) {
        min_i = (8192 + i - 1 - 4) > (0 + t - 1) ? (8192 + i - 1 - 4) : (0 + t - 1);
        max_i = (8192 + i - 1 + 4) < (8192 + t - 1) ? (8192 + i - 1 + 4) : (8192 + t - 1);
        min_j = (8192 + j - 1 - 4) > (0 + t - 1) ? (8192 + j - 1 - 4) : (0 + t - 1);
        max_j = (8192 + j - 1 + 4) < (8192 + t - 1) ? (8192 + j - 1 + 4) : (8192 + t - 1);
        tmp += filter[t] * orig[max_i * 8192 + max_j];
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}
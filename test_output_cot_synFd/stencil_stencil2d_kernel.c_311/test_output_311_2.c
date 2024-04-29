#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int t_i;
  int t_j;
  int t_k;
  int t_k_min;
  int t_k_max;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 64; j++) {
      t_i = i - 1;
      if (t_i < 0) {
        t_i = 0;
      }
      t_j = j - 1;
      if (t_j < 0) {
        t_j = 0;
      }
      t_k_min = t_i * 64 + t_j;
      t_k = t_k_min;
      t_k_max = t_k_min + 8;
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{14}
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
      for ( ; t_k < t_k_max; t_k++) {
        tmp += filter[t_k - t_k_min] * orig[t_k];
      }
      sol[i * 64 + j] = tmp;
    }
  }
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int oidx;
  int sol_idx;
  int filter_idx;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 128 + 2; j++) {
      sol_idx = i * 128 + j;
      oidx = (i - 1) * 128 + (j - 1);
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (filter_idx = 0; filter_idx < 9; filter_idx++) {
        idx = oidx + filter[filter_idx];
        t += orig[idx] * filter[filter_idx];
      }
      sol[sol_idx] = t;
    }
  }
}
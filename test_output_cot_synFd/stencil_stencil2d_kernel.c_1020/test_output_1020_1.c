#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int tmp_idx = i + ((k / 3) - 1);
        int tmp_idx_1 = j + ((k % 3) - 1);
        if (tmp_idx > 0 && tmp_idx < 8192 && tmp_idx_1 > 0 && tmp_idx_1 < 8192) {
          sol[idx] += filter[k] * orig[tmp_idx * 8192 + tmp_idx_1];
        }
      }
      sol[idx] = sol[idx] / 9.0;
    }
  }
}
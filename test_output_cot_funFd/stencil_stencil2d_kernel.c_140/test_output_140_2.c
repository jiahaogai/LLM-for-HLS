#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    inner:
    for (j = 0; j < 128; j++) {
      idx = i * 128 + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      filter_idx:
      for (k = 0; k < 9; k++) {
        int tmp_idx = idx + k - center;
        if (tmp_idx < 0) {
          tmp_idx = -tmp_idx;
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        filter_val:
        for (int tmp_val = 0; tmp_val < 9; tmp_val++) {
          if (tmp_idx == tmp_val) {
            sol[idx] += orig[tmp_idx * 128 + j] * filter[tmp_val];
          }
        }
      }
    }
  }
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 8; j++) {
      t = 0;
      int idx = (((pad - 1) + (i * 8)) * 8) + (pad - 1) + j;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (int filter_i = 0; filter_i < 3; filter_i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (int filter_j = 0; filter_j < 3; filter_j++) {
          int filter_idx = (filter_i * 3) + filter_j;
          t += orig[idx + (filter_idx - 1)] * filter[filter_idx];
        }
      }
      sol[idx] = t;
    }
  }
}
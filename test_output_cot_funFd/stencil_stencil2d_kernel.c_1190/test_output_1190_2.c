#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 2; i < 128 - 2; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    for (j = 2; j < 64 - 2; j++) {
      val = 0;
      idx = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        int cur_filter;
        int cur_idx;
        int cur_val;
        cur_filter = filter[k];
        cur_idx = (i + ((k - 4) >> 2)) * 64 + j + ((k - 4) & 0x03);
        cur_val = orig[cur_idx];
        val += cur_filter * cur_val;
        idx += cur_filter;
      }
      sol[i * 64 + j] = val / idx;
    }
  }
}
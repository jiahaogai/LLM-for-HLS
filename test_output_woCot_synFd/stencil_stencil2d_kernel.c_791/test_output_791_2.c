Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{2}
      inner:
      for (k = 0; k < 9; k++) {
        int cur_filter;
        int cur_idx;
        cur_filter = filter[k];
        cur_idx = idx + my_offset[k];
        val += cur_filter * orig[cur_idx];
      }
      sol[idx] = val;
    }
  }
//#pragma endscop
}
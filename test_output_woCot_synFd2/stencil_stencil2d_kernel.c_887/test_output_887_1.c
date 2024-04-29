#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + ((0 - (4 + (k / 5)))) ;
        idx = (k_col * 256) + j + ((0 - (4 + (k % 5)))) ;
        if (((k_col >= 0) && (k_col < 256))) {
          if ((j >= 0) && (j < 256)) {
            val += ((orig[idx]) * (filter[k])) ;
          }
        }
      }
      sol[((i * 256) + j)] = val;
    }
  }
}
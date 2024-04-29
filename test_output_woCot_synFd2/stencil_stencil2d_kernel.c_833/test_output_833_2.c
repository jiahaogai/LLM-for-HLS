#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = -4; k < 5; k++) {
        int cur;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_middle:
        for (int inner_j = 0; inner_j < 8; inner_j++) {
          int tmp_inner_j = inner_j + j;
          if (tmp_inner_j < 0 || 256 <= tmp_inner_j) {
            cur = 0;
          }
           else {
            cur = orig[i * 256 + tmp_inner_j];
          }
          result += cur * filter[k + 4];
        }
      }
      sol[i * 256 + j] = result;
    }
  }
}
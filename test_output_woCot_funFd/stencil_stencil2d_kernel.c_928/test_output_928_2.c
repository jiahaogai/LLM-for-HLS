#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  int flatten_filter_index;
  int flatten_idx;
  int idx;
  int idy;
  int filter_element;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 4; j++) {
      flatten_idx = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      loop_flatten_filter_index:
      for (flatten_filter_index = 0; flatten_filter_index < 3; flatten_filter_index++) {
        
#pragma ACCEL PIPELINE auto{off}
        loop_jj:
        for (idx = j - 1; idx <= j + 1; idx++) {
          if (idx < 0) {
            idx = 0;
          }
          if (idx > 3) {
            idx = 3;
          }
          
#pragma ACCEL PIPELINE auto{off}
          loop_ii:
          for (idy = i - 1; idy <= i + 1; idy++) {
            if (idy < 0) {
              idy = 0;
            }
            if (idy > 3) {
              idy = 3;
            }
            filter_element = filter[flatten_filter_index][(idx - j + 1) + 1 - ((idx - j + 1) > 3?) 3 : 0];
            sol[idy][idx] += orig[idy][idx] * filter_element;
          }
        }
      }
    }
  }
}
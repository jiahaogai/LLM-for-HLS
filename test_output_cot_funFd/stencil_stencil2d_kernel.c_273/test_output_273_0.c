#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_dw;
  int tmp;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_row:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_up:
    for (row_up = -1; row_up <= 1; row_up++) {
      row = i * 64 + row_up;
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      loop_filter_elem:
      for (filter_elem = 0; filter_elem < 9; filter_elem++) {
        t = filter[filter_elem];
        j = filter_elem - 4;
        tmp += t * orig[row * 64 + j];
      }
      sol[row * 64] = tmp;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_row_dw:
    for (row_dw = -1; row_dw <= 1; row_dw++) {
      row = (i + 1) * 64 + row_dw;
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{2}
      loop_filter_elem:
      for (filter_elem = 0; filter_elem < 9; filter_elem++) {
        t = filter[filter_elem];
        j = filter_elem - 4;
        tmp += t * orig[row * 64 + j];
      }
      sol[row * 64] = tmp;
    }
  }
}
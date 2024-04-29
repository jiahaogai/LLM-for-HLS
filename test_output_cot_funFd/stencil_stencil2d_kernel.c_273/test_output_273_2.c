Code: #pragma ACCEL kernel

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
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_dw;
  int col;
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_col:
    for (j = 1; j < 8191; j++) {
      t = 0;
      int loop_filt[] = {4, 3, 2, 1, 0, 1, 2, 3, 4};
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_filt:
      for (row = -4; row <= 4; row++) {
        int loop_up[] = {8190, 8188, 8186, 8184, 8182, 8180, 8178, 8176};
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
        loop_up:
        for (col = -4; col <= 4; col++) {
          row_up = i + row;
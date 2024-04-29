#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
  for (j = 8; j < 8184; j++) {
    row = j * 64;
    row_up = (j - 8) * 64;
    row_down = (j + 8) * 64;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 8; i < 8184; i++) {
      col = i * 64;
      col_up = (i - 8) * 64;
      col_down = (i + 8) * 64;
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = -4; k <= 4; k++) {
        t += filter[4 + k] * orig[row_up + col_up + k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = -4; k <= 4; k++) {
        t += filter[4 + k] * orig[row_up + col + k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = -4; k <= 4; k++) {
        t += filter[4 + k] * orig[row_up + col_down + k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = -4; k <= 4; k++) {
        t += filter[4 + k] * orig[row + col_up + k];
      }
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = -4; k <= 4; k++) {
        t += filter[4 + k] * orig[row + col + k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = -4; k <= 4; k++) {
        t += filter[4 + k] * orig[row + col_down + k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = -4; k <= 4; k++) {
        t += filter[4 + k] * orig[row_down + col_up + k];
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = -4; k <= 4; k++) {
        t += filter[4 + k] * orig[row_down + col + k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = -4; k <= 4; k++) {
        t += filter[4 + k] * orig[row_down + col_down + k
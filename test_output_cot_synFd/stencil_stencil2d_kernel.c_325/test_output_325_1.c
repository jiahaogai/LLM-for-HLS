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
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (row = i - 1; row <= i + 1; row++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
        inner_1:
        for (col = j - 1; col <= j + 1; col++) {
          t += orig[row * 8192 + col] * filter[col - j + 1];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}
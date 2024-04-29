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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      row = i * 8 + j;
      row_up = (i - 1) * 8 + j;
      row_dw = (i + 1) * 8 + j;
      tmp = orig[row_up] + orig[row_dw] + orig[row] + orig[row_up + 1] + orig[row_dw + 1];
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (t = 0; t < 9; t++) {
        if (((tmp - filter[t]) <= 0)) {
          t = 1;
        }
      }
      sol[row] = t;
    }
  }
}
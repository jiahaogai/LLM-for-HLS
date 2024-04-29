Code: #pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (r = 0; r < 128; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (c = 0; c < 64; c++) {
      double sum = 0.0;
      int k_row;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k_row = 0; k_row < 3; k_row++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
        inner_1:
        for (k_col = 0; k_col < 3; k_col++) {
          int k = (k_row * 3) + k_col;
          int i_row = r + (-1 + k_row);
          int i_col = c + (-1 + k_col);
          mult = filter[k] * orig[i_row * 64 + i_col];
          sum += mult;
        }
      }
      sol[r * 64 + c] = sum;
    }
  }
}
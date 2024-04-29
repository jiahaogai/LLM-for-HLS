#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    sum = 0.0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    inner:
    for (j = 0; j < 9; j++) {
      k_col = i % 64;
      k_row = (i - k_col) / 64;
      k = k_row + (j - 4);
      if (k_col < 4) {
        k_col = 4;
      }
      
      if (k_col > 60) {
        k_col = 60;
      }
      
      if (k_row < 4) {
        k_row = 4;
      }
      
      if (k_row > 60) {
        k_row = 60;
      }
      
      if (k < 0) {
        k = 0;
      }
      
      if (k > 8190) {
        k = 8190;
      }
      
      sum += filter[j] * orig[k * 64 + k_col];
    }
    sol[i] = sum;
  }
}
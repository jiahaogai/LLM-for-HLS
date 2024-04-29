#pragma ACCEL kernel

void stencil(double orig[64][128],double sol[64][128],double filter[2][2])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 128 - 1; j++) {
      double sum = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k_col = 0; k_col < 2; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k_row = 0; k_row < 2; k_row++) {
          int k = k_row * 2 + k_col;
          sum += filter[k_row][k_col] * orig[i + k_row - 1][j + k_col - 1];
        }
      }
      sol[i][j] = sum;
    }
  }
//#pragma endscop
}
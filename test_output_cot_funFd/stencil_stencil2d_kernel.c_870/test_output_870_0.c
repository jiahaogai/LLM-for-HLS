#pragma ACCEL kernel

void stencil(double orig[64][128],double sol[64][128],double filter[4][4])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 128 - 1; j++) {
      double sum = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k_col = 0; k_col < 4; k_col++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        for (k_row = 0; k_row < 4; k_row++) {
          int cur_k = 2 + k_row;
          int cur_j = 2 + k_col;
          int cur_i = i + k_row;
          sum += filter[k_row][k_col] * orig[cur_i][cur_j];
        }
      }
      sol[i][j] = sum;
    }
  }
//#pragma endscop
}
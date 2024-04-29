#pragma ACCEL kernel

void stencil(double orig[40][40],double sol[40][40],double filter[3][3])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 39; j++) {
      sol[i][j] = 0.0;
      k_col = -1;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (k_col <= 1) {
        k_row = -1;
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        while (k_row <= 1) {
          k_row += 1;
          k_col += 1;
          k = k_row * 3 + k_col;
          sol[i][j] += filter[k_row + 1][k_col + 1] * orig[i + k_row][j + k_col];
        }
      }
    }
  }
//#pragma endscop
}
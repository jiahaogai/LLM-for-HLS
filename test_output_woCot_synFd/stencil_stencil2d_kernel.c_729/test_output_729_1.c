#pragma ACCEL kernel

void stencil(double orig[400][400],double sol[400][400],double filter[3][3])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 400 - 1; j++) {
      sol[i][j] = 0.0;
      for (k_col = 0; k_col < 3; k_col++) {
        int tmp_col = j + (-1 + k_col);
        for (k_row = 0; k_row < 3; k_row++) {
          int tmp_row = i + (-1 + k_row);
          sol[i][j] += filter[k_row][k_col] * orig[tmp_row][tmp_col];
        }
      }
    }
  }
//#pragma endscop
}
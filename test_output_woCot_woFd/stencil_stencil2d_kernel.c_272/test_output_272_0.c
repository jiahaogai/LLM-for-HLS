#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 400 - 1; j++) {
      sol[i][j] = 0;
      inner:
      for (k = 0; k < 25; k++) {
        i_col = i - 1 + ((k / 5) - 1);
        j_col = j - 1 + ((k % 5) - 1);
        k_col = filter[k];
        sol[i][j] += orig[i_col][j_col] * k_col;
      }
    }
  }
}
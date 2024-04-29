#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{126}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 400 - 1; j++) {
      sol[i][j] = ((filter[0] * orig[i][j - 1]) + (filter[1] * orig[i][j + 1]) + (filter[2] * orig[i + 1][j - 1]) + (filter[3] * orig[i + 1][j]) + (filter[4] * orig[i + 1][j + 1]) + (filter[5] * orig[i - 1][j - 1]) + (filter[6] * orig[i - 1][j]) + (filter[7] * orig[i - 1][j + 1]) + (filter[8] * orig[i][j])) / 256;
/* Standardize from: 0 <= i,j < 400 */
i_col = ((400 + 1) * (i / (400 + 1))) + 1;
j_col = ((400 + 1) * (j / (400 + 1))) + 1;
k_col = 0;
kernel:
      while (k_col < (400 + 1)) {
        if (i_col == ((400 + 1) * ((k_col - 1) / (400 + 1))) + 1 && j_col == ((400 + 1) * ((k_col - 1) % (400 + 1)))) {
          break;
        }
        k_col++;
      }
      k = k_col - 1;
      if (((i_col - 1) == ((400 + 1) * ((k - 1) / (400 + 1)))) && ((j_col - 1) == ((400 + 1) * ((k - 1) % (400 + 1))))) {
        sol[i][j] = orig[k][k];
      }
    }
  }
}
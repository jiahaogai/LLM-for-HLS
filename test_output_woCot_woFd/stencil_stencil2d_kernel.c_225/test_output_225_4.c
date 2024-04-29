#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 8; i < 8184 - 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8192 - 8; j++) {
      result = ((orig[i - 8][j - 8] + orig[i - 8][j - 7] + orig[i - 8][j - 6] + orig[i - 8][j - 5] + orig[i - 8][j - 4] + orig[i - 8][j - 3] + orig[i - 8][j - 2] + orig[i - 8][j - 1] + orig[i - 8][j]) + (orig[i - 7][j - 8] + orig[i - 7][j - 7] + orig[i - 7][j - 6] + orig[i - 7][j - 5] + orig[i - 7][j - 4] + orig[i - 7][j - 3] + orig[i - 7][j - 2] + orig[i - 7][j - 1] + orig[i - 7][j]) + (orig[i - 6][j - 8] + orig[i - 6][j - 7] + orig[i - 6][j - 6] + orig[i - 6][j - 5] + orig[i - 6][j - 4] + orig[i - 6][j - 3] + orig[i - 6][j - 2] + orig[i - 6][j - 1] + orig[i - 6][j]) + (orig[i - 5][j - 8] + orig[i - 5][j - 7] + orig[i - 5][j - 6] + orig[i - 5][j - 5] + orig[i - 5][j - 4] + orig[i - 5][j - 3] + orig[i - 5][j - 2] + orig[i - 5][j - 1] + orig[i - 5][j]) + (orig[i - 4][j - 8] + orig[i - 4][j - 7] + orig[i - 4][j - 6] + orig[i - 4][j - 5] + orig[i - 4][j - 4] + orig[i - 4][j - 3] + orig[i - 4][j - 2] + orig[i - 4][j - 1] + orig[i - 4][j]) + (orig[i - 3][j - 8] + orig[i - 3][j - 7] + orig[i - 3][j - 6] + orig[i - 3][j - 5] + orig[i - 3][j - 4] + orig[i - 3][j - 3] + orig[i - 3][j - 2] + orig[i - 3][j - 1] + orig[i - 3][j]) + (orig[i - 2][j - 8] + orig[i - 2][j - 7] + orig[i - 2][j - 6] + orig[i - 2][j - 5] + orig[i - 2][j - 4] + orig[i - 2][j - 3] + orig[i - 2][j - 2] + orig[i - 2][j - 1] + orig[i - 2][j]) + (orig[i - 1][j - 8] + orig[i - 1][j - 7] + orig[i - 1][j - 6] + orig[i - 1][j - 5] + orig[i - 1][j - 4] + orig[i - 1][j - 3] + orig[i - 1][j - 2] + orig[i - 1][j - 1] + orig[i - 1][j]) + (orig[i][j - 8] + orig[i][j - 7] + orig[i][j - 6] + orig[i][j - 5] + orig[i][j - 4] + orig[i][j - 3] + orig[i][j - 2] + orig[i][j - 1] + orig[i][j])) * filter[4];
      result += ((orig[i + 5][j - 8] + orig[i + 5][j - 7] + orig[i + 5][j - 6] + orig[i + 5][j - 5] + orig[i + 5][j - 4] + orig[i + 5][j - 3] + orig[i + 5][j - 2] + orig[i + 5][j - 1] + orig[i + 5][j]) + (orig[i + 6][j - 8] + orig[i + 6][j - 7] + orig[i + 6][j - 6] + orig[i + 6][j - 5] + orig[i + 6][j - 4] + orig[i + 6][j - 3] + orig[i + 6][j - 2] + orig[i + 6][j - 1] + orig[i + 6][j]) + (orig[i + 7][j - 8] + orig[i + 7][j - 7] + orig[i + 7][j - 6] + orig[i + 7][j - 5] + orig[i + 7][j - 4] + orig[i + 7][j - 3] + orig[i + 7][j - 2] + orig[i + 7][j - 1] + orig[i + 7][j]) + (orig[i + 8][j - 8] + orig[i + 8][j - 7] + orig[i + 8][j - 6] + orig[i + 8][j - 5] + orig[i + 8][j - 4] + orig[i + 8][j - 3] + orig[i + 8][j - 2] + orig[i + 8][j - 1] + orig[i + 8][j])) * filter[3];
      result += ((orig[i + 1][j - 8] + orig[i + 1][j - 7] + orig[i + 1][j - 6] + orig[i + 1][j - 5] + orig[i + 1][j - 4] + orig[i + 1][j - 3] + orig[i + 1][j - 2] + orig[i + 1][j - 1] + orig[i + 1][j]) * filter[2]) + ((orig[i + 2][j - 8] + orig[i + 2][j - 7] + orig[i + 2][j - 6] + orig[i + 2][j - 5] + orig[i + 2][j - 4] + orig[i + 2][j - 3] + orig[i + 2][j - 2] + orig[i + 2][j - 1] + orig[i + 2][j]) * filter[1]) + ((orig[i + 3][j - 8] + orig[i + 3][j - 7] + orig[i + 3][j - 6] + orig[i + 3][j - 5] + orig[i + 3][j - 4] + orig[i + 3][j - 3] + orig[i + 3][j - 2] + orig[i + 3][j - 1] + orig[i + 3][j]) * filter[0]);
      sol[i][j] = result;
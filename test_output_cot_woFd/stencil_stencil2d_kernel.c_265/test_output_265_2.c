#pragma ACCEL kernel

void stencil(double A[25][25],double B[25][25])
{
  int r;
  int c;
  int i;
  int j;
  double mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (c = 0; c < 25; c++) {
      mul = 0.0;
      i = r - 1;
      while (i < r + 2) {
        j = c - 1;
        while (j < c + 2) {
          mul += A[i][j] * B[i][j];
          j++;
        }
        i++;
      }
      A[r][c] = mul;
    }
  }
}
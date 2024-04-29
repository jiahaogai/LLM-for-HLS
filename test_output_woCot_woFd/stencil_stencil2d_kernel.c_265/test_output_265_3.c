#pragma ACCEL kernel

void stencil(double A[25][25],double B[25][25])
{
  int r;
  int c;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (c = 0; c < 25; c++) {
      B[r][c] = 0.2 * A[r][c] + 0.3 * A[r][c + 1] + 0.4 * A[r][c + 2] + 0.3 * A[r + 1][c] + 0.2 * A[r + 2][c];
    }
  }
//#pragma endscop
}
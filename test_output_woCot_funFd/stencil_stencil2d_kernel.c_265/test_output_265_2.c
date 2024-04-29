#pragma ACCEL kernel

void stencil(int rows,int cols,int A[cols][rows],int B[cols][rows])
{
  int r;
  int c;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (r = 1; r < rows - 1; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (c = 1; c < cols - 1; c++) {
      int v = A[r][c];
      B[r][c] = (v - 1) * (v - cols - 2) - B[r - 1][c - 1] - B[r - 1][c] - B[r - 1][c + 1] - B[r][c - 1] - B[r][c + 1] - B[r + 1][c - 1] - B[r + 1][c] - B[r + 1][c + 1];
    }
  }
//#pragma endscop
}
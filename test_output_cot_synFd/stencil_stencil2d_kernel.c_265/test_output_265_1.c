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
      B[r][c] = (v + A[r - 1][c - 1] + A[r - 1][c] + A[r - 1][c + 1] + A[r][c - 1] + A[r][c + 1] + A[r + 1][c - 1] + A[r + 1][c] + A[r + 1][c + 1]) / 9;
    }
  }
//#pragma endscop
}
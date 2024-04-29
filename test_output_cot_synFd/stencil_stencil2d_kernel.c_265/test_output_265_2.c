#pragma ACCEL kernel

void stencil(int rows,int cols,int A[200][250],int B[200][250])
{
  int r;
  int c;
  int t;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (r = 1; r <= 200 - 2; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (c = 1; c <= 250 - 2; c++) {
      t = A[r - 1][c - 1] + A[r - 1][c + 1] + A[r + 1][c - 1] + A[r + 1][c + 1] + A[r][c];
      B[r][c] = t / 250;
    }
  }
//#pragma endscop
}
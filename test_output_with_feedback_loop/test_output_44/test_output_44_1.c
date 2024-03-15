#pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int B[25][20][30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 30; p++) {
        B[r][q][p] = ((long )r) * ((long )p) * 3 + ((long )q) * 2 + 1;
      }
    }
    for (p = 0; p < 30; p++) {
      A[r][0][p] = B[r][0][p];
    }
    for (s = 1; s < 20; s++) {
      for (p = 0; p < 30; p++) {
        A[r][s][p] = A[r][s - 1][p] + B[r][s][p];
      }
    }
    for (p = 0; p < 30; p++) {
      A[r][20][p] = B[r][20][p];
    }
  }
//#pragma endscop
}
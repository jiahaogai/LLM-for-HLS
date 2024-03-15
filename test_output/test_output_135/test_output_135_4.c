
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
        B[r][q][p] = ((long )0);
      }
    }
    for (p = 0; p < 30; p++) {
      A[r][0][p] = B[r][0][p];
    }
    for (q = 0; q < 20; q++) {
      A[r][q][0] = B[r][q][0];
    }
    for (s = 1; s < 30; s++) {
      for (q = 0; q < 20; q++) {
        A[r][q][s] = A[r][q][s - 1] + B[r][q][s];
      }
    }
    for (p = 1; p < 20; p++) {
      for (q = 0; q < 20; q++) {
        A[r][q][p] = A[r][q][p] + A[r][p][q];
      }
    }
  }
//#pragma endscop
}

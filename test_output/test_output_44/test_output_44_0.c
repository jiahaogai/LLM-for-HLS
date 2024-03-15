
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
    for (s = 0; s < 30; s++) {
      for (q = 0; q < 20; q++) {
        for (p = 0; p < 30; p++) {
          if (p < s) {
            B[r][q][p] += A[r][q][s] * B[r][q][s];
          }
        }
      }
    }
    for (s = 0; s < 30; s++) {
      for (q = 0; q < 20; q++) {
        for (p = 0; p < 30; p++) {
          if (s < p) {
            B[r][q][p] += A[r][q][s] * B[r][q][s];
          }
        }
      }
    }
  }
//#pragma endscop
}

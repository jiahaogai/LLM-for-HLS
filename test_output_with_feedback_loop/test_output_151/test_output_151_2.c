#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[25][20][30])
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
        A[r][q][p] = ((double )0);
      }
    }
    for (p = 0; p < 30; p++) {
      A[r][14][p] = 4.0;
    }
    for (q = 0; q < 20; q++) {
      A[r][q][14] = 4.0;
    }
    for (s = 0; s < 1; s++) {
      for (q = 0; q < 20; q++) {
        for (p = 0; p < 30; p++) {
          A[r][q][p] += ((double )(((int )(((double )10.0) * 
                                         sin(((double )(s + 1) * 
                                              p / 30.0))))) * C4[r][q][p]);
        }
      }
    }
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      for (p = 0; p < 30; p++) {
        C4[r][q][p] = A[r][q][p];
      }
    }
  }
//#pragma endscop
}
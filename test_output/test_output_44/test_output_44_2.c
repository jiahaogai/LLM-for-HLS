
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
        B[r][q][p] = A[r][q][p];
      }
    }
    for (s = 0; s < 30; s++) {
      for (q = 0; q < 20; q++) {
        int _in_val = A[r][q][s];
        B[r][q][s] = _in_val * ((_in_val > 0.0) ? 1.0 : -1.0);
      }
    }
  }
//#pragma endscop
}

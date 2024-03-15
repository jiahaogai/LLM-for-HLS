#pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,double A[25][20][30])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int a;
  int b;
  double Ar_pS;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    loop_q:
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      loop_p:
      for (p = 0; p < 30; p++) {
        Ar_pS = A[r][q][p];
        loop_a:
        for (a = 0; a < 5; a++) {
          loop_b:
          for (b = 0; b < 4; b++) {
            A[r][a + q][b + p] = Ar_pS * A[a + q][b + p][p];
          }
        }
        A[r][q][p] = Ar_pS;
      }
    }
  }
}
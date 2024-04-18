#pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,double A[25][20][30],double B[20][25][30],double C4[30][30])
{
  int r;
  int q;
  int p;
  int a;
  int b;
  int k;
  double temp;
  double mul;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_r:
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_q:
    for (q = 0; q < 30; q++) {
      temp = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      loop_k:
      for (k = 0; k < 20; k++) {
        loop_a:
        for (a = 0; a < 5; a++) {
          mul = A[a][k][r] * B[k][a][q];
          loop_b:
          for (b = 0; b < 5; b++) {
            temp += mul * B[a][b][q];
          }
        }
      }
      C4[r][q] = temp;
    }
  }
}
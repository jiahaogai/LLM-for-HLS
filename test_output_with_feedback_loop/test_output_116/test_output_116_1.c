#pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,double A[25][20][30],double B[25][30][40],double C[25][40][50])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  double temp1;
  double temp2;
  
#pragma ACCEL PIPELINE auto{}
  
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
        loop_s:
        for (s = 0; s < 30; s++) {
          temp1 = A[r][q][s] * B[r][s][p];
          loop_t:
          for (t = 0; t < 40; t++) {
            temp2 = temp1 * C[q][t][p];
            loop_u:
            for (u = 0; u < 50; u++) {
              A[r][t][u] += temp2;
            }
          }
        }
      }
    }
  }
}
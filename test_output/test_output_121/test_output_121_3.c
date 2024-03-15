
 #pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,double A[25][20][30],double C4[30][30],double B[25][30],double D[20][30],double E[25][20])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  
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
        loop_s:
        for (s = 0; s < 30; s++) {
          A[r][q][p] += D[q][s] * C4[p][s];
        }
      }
      loop_t:
      for (t = 0; t < 20; t++) {
        loop_u:
        for (u = 0; u < 30; u++) {
          B[r][q][u] += E[t][q] * A[t][q][u];
        }
      }
    }
  }
}

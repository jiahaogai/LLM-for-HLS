
 #pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,int nq2,double A[25][20][30],double C4[30][30],double B[25][20])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  double tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    loop_q:
    for (q = 0; q < 20; q++) {
      loop_s:
      for (s = 0; s < 30; s++) {
        A[r][q][s] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_r_2:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    loop_q_2:
    for (q = 0; q < 20; q++) {
      loop_p:
      for (p = 0; p < 30; p++) {
        loop_t:
        for (t = 0; t < 30; t++) {
          tmp = A[r][q][t] * B[t][p];
          A[r][q][p] = A[r][q][p] + tmp;
        }
      }
      loop_s_2:
      for (s = 0; s < 30; s++) {
        C4[p][s] = ((double )0);
      }
      loop_s_1:
      for (s = 0; s < 30; s++) {
        loop_t_1:
        for (t = 0; t < 30; t++) {
          C4[p][s] = C4[p][s] + A[r][q][t] * B[t][s];
        }
      }
      loop_cp:
      for (p = 0; p < 30; p++) {
        B[r][q] = C4[p][s];
      }
    }
  }
}

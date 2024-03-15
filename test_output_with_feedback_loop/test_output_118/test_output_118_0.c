#pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,double A[25][20][30],double C4[30][30],double B[25][30],double D[20][30],double E[25][20])
{
  int r;
  int q;
  int p;
  int j;
  int k;
  int i;
  
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
        A[r][q][p] = ((double )0);
      }
    }
    loop_j:
    for (j = 0; j < 30; j++) {
      loop_k:
      for (k = 0; k < 20; k++) {
        double Bjk = B[r][j] * D[k][j];
				loop_i:
        for (i = 0; i < 30; i++) {
          A[r][k][i] += Bjk * E[q][i];
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_j_1:
  for (j = 0; j < 30; j++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    loop_k_1:
    for (k = 0; k < 30; k++) {
      C4[j][k] = ((double )0);
      
#pragma ACCEL PARALLEL reduction=C4 FACTOR=auto{__PARA__L4}
      loop_r_1:
      for (r = 0; r < 25; r++) {
        loop_q_1:
        for (q = 0; q < 20; q++) {
          C4[j][k] += A[r][q][k] * D[q][r];
        }
      }
    }
  }
}
#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[25][25][30][35],double sum[25][35])
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
    for (q = 0; q < 25; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 30; p++) {
        sum[r][q] += A[r][p][0] * C4[q][p][0][s] + A[r][p][1] * C4[q][p][1][s] + A[r][p][2] * C4[q][p][2][s] + A[r][p][3] * C4[q][p][3][s];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (s = 0; s < 35; s++) {
      double sum_tmp = sum[r][0] + sum[r][1] + sum[r][2] + sum[r][3] + sum[r][4] + sum[r][5] + sum[r][6] + sum[r][7] + sum[r][8] + sum[r][9] + sum[r][10] + sum[r][11] + sum[r][12] + sum[r][13] + sum[r][14] + sum[r][15] + sum[r][16] + sum[r][17] + sum[r][18] + sum[r][19];
      C4[r][0][0][s] = sum_tmp;
    }
  }
//#pragma endscop
}
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
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 25; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{4}
      for (p = 0; p < 30; p++) {
        sum[r][q] += A[r][p][0] * C4[q][p][0][s] + A[r][p][1] * C4[q][p][1][s] + A[r][p][2] * C4[q][p][2][s] + A[r][p][3] * C4[q][p][3][s];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (q = 0; q < 25; q++) {
      for (s = 0; s < 35; s++) {
        C4[r][q][0][s] = sum[r][s] + C4[q][r][0][s];
      }
    }
  }
//#pragma endscop
}
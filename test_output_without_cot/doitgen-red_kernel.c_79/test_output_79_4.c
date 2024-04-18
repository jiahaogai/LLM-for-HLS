#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[25][25][30][30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 25; q++) {
      double Ar_tmp = A[r][0][0] * C4[q][r][0][0] + A[r][0][1] * C4[q][r][0][1] + A[r][0][2] * C4[q][r][0][2];
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 1; p < 20; p++) {
        Ar_tmp += A[r][p][0] * C4[q][r][p][0] + A[r][p][1] * C4[q][r][p][1] + A[r][p][2] * C4[q][r][p][2];
      }
      A[r][0][0] = Ar_tmp;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 25; q++) {
      double C4rq_tmp = A[q][0][0] * C4[r][q][0][0] + A[q][0][1] * C4[r][q][0][1] + A[q][0][2] * C4[r][q][0][2];
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (p = 1; p < 20; p++) {
        for (s = 0; s < 30; s++) {
          C4rq_tmp += A[q][p][0] * C4[r][q][p][s] * C4[r][s][p][0] + A[q][p][1] * C4[r][q][p][s] * C4[r][s][p][1] + A[q][p][2] * C4[r][q][p][s] * C4[r][s][p][2];
        }
      }
      A[r][0][0] = C4rq_tmp;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    for (q = 0; q < 25; q++) {
      double sum_tmp = A[r][0][0];
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L5}
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      for (p = 0; p < 20; p++) {
        for (s = 0; s < 30; s++) {
          sum_tmp += A[q][p][0] * C4[r][q][p][s] * A[s][0][0];
        }
      }
      A[r][0][0] = sum_tmp;
    }
  }
//#pragma endscop
}
#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 30; p++) {
        sum[p] = 0.0;
        for (s = 0; s < 30; s++) {
          sum[p] += A[r][q][s] * C4[s][p];
        }
      }
    }
    for (p = 0; p < 30; p++) {
      A[r][0][p] = sum[p];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    for (q = 0; q < 20; q++) {
      for (p = 0; p < 30; p++) {
        double sum_tmp = 0.0;
        for (s = 0; s < 30; s++) {
          sum_tmp += A[r][s][p] * A[s][q][p];
        }
        A[r][q][p] = sum_tmp;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  for (p = 0; p < 30; p++) {
    for (r = 0; r < 25; r++) {
      sum[p] = A[r][0][p];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  for (p = 0; p < 30; p++) {
    for (r = 0; r < 25; r++) {
      for (q = 0; q < 20; q++) {
        C4[p][q] = sum[p] + A[r][q][p];
      }
    }
  }
//#pragma endscop
}
void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  double temp21;
  double mul18;
  double mul19;
  double mul22;
  double mul23;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 30; q++) {
      temp21 = A[0][0][r] * C4[0][q];
      sum[r] = sum[r] + temp21;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (p = 0; p < 20; p++) {
      for (q = 0; q < 30; q++) {
        mul18 = A[p][0][r] * C4[q][p];
        sum[r] = sum[r] + mul18;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    for (p = 0; p < 25; p++) {
      for (q = 0; q < 30; q++) {
        mul19 = A[p][1][r] * C4[q][p];
        sum[r] = sum[r] + mul19;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    for (p = 0; p < 25; p++) {
      for (q = 0; q < 30; q++) {
        mul22 = A[p][3][r] * C4[q][p];
        sum[r] = sum[r] + mul22;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L8}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L9}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
    for (p = 0; p < 25; p++) {
      for (q = 0; q < 30; q++) {
        mul23 = A[p][4][r] * C4[q][p];
        sum[r] = sum[r] + mul23;
      }
    }
  }
}
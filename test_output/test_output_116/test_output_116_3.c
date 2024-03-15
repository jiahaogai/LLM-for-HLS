
#pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int B[25][20][30],int C[25][20][30])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int i;
  int j;
  int k;
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
        A[r][q][p] = ((long )r) * ((long )p) * 64 + ((long )q) * 64;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      for (p = 0; p < 30; p++) {
        B[r][q][p] = 1.0;
        for (i = 0; i < 5; i++) {
          s = r + ((long )i) * 5;
          B[s][q][p] *= A[r][q][p];
        }
        for (i = 0; i < 5; i++) {
          s = r - ((long )i) * 5;
          if (s >= 0 && s < 25) {
            B[s][q][p] *= A[r][q][p];
          }
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L8}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
      for (p = 0; p < 30; p++) {
        C[r][q][p] = 0.0;
        for (i = 0; i < 5; i++) {
          t = q + ((long )i) * 5;
          C[r][q][p] += B[r][t][p];
        }
        for (i = 0; i < 5; i++) {
          t = q - ((long )i) * 5;
          if (t >= 0 && t < 20) {
            C[r][q][p] += B[r][t][p];
          }
        }
      }
    }
  }
//#pragma endscop
}

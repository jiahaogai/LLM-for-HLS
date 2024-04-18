#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30][40])
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
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 30; p++) {
        A[r][q][p] = ((double )0);
      }
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (p = 0; p < 30; p++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (s = 0; s < 40; s++) {
        for (q = 0; q < 20; q++) {
          A[r][q][p] += C4[p][s][r] * C4[s][q][r];
        }
      }
    }
  }
//#pragma endscop
}
#pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int C4[30][30],int sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 30; q++) {
      sum[q] = ((int )0);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (p = 0; p < 25; p++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (s = 0; s < 20; s++) {
        for (q = 0; q < 30; q++) {
          sum[q] = sum[q] + A[p][s][q] * C4[s][q];
        }
      }
      for (q = 0; q < 30; q++) {
        A[p][14][q] = sum[q];
      }
    }
  }
//#pragma endscop
}
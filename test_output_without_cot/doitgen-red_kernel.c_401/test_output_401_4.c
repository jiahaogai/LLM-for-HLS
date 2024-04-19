#pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int C4[30][30],int sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 30; p++) {
        sum[p] = ((int )0);
      }
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (s = 0; s < 30; s++) {
        #pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L2}
        for (p = 0; p < 30; p++) {
          sum[s] += A[r][q][p] * C4[p][s];
        }
      }
      for (p = 0; p < 30; p++) {
        A[r][q][p] = sum[p];
      }
    }
  }
//#pragma endscop
}
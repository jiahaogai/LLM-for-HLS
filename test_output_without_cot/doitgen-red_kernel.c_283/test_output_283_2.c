#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 30; q++) {
      sum[r] = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L5}
      for (p = 0; p < 20; p++) {
        for (s = 0; s < 5; s++) {
          sum[r] += A[p][s][r] * C4[q][s];
        }
      }
    }
  }
//#pragma endscop
}
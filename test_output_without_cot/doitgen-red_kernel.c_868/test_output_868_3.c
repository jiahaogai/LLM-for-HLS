#pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int C4[30][30],int sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 30; q++) {
      sum[q] = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L2}
      for (p = 0; p < 25; p++) {
        s = 0;
        
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{__PARA__L3}
        for (s = 0; s < 20; s++) {
          sum_tmp = sum[q] + A[p][s][r];
          C4[p][q] = sum_tmp;
          sum[q] = sum_tmp + A[p][s][r];
        }
      }
    }
  }
//#pragma endscop
}
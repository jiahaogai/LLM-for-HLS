#pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int C4[30][30],int sum[30])
{
  int r;
  int q;
  int p;
  int s;
  int temp;
  int mul1;
  int mul2;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    loop_q:
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      loop_p:
      for (p = 0; p < 30; p++) {
        sum[p] = 0;
        loop_s:
        for (s = 0; s < 30; s++) {
          temp = A[r][q][s] * A[s][q][p];
          sum[p] += temp;
        }
        mul1 = C4[q][p] * sum[p];
        mul2 = 0.0;
        loop_ms:
        for (s = 0; s < 30; s++) {
          mul2 += A[r][q][s] * A[s][q][p] * ((s == p) ? 1.0 : mul1);
        }
        A[r][q][p] = mul2;
      }
    }
  }
}
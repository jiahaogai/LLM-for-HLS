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
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_q:
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      loop_p:
      for (p = 0; p < 30; p++) {
        sum[p] = 0;
        loop_s:
        for (s = 0; s < 30; s++) {
          temp = A[r][q][s] * A[r][s][p];
          sum[p] += temp;
        }
        mul1 = q + 1;
        mul2 = p + 1;
        C4[mul1][mul2] = sum[p];
      }
    }
  }
}
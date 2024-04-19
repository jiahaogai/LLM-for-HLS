#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,double A[20][22],double B[22][24],double C4[20][24],double sum[20])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{30}
    for (j = 0; j < 24; j++) {
      sum[i] = ((double )0);
      for (k = 0; k < 22; k++) {
        sum[i] += A[i][k] * B[k][j];
      }
      C4[i][j] = sum[i];
    }
  }
//#pragma endscop
}
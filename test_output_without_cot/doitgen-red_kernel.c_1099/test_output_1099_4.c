#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,double A[200][240],double B[240][200],double C4[200][200],double sum[200])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{30}
    for (j = 0; j < 200; j++) {
      sum_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=A_tmp FACTOR=auto{1}
      for (k = 0; k < 240; k++) {
        A_tmp = A[i][k] * B[k][j];
        sum_tmp += A_tmp;
      }
      sum[j] = sum_tmp;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 0; j < 200; j++) {
      C4[i][j] = sum[j];
    }
  }
//#pragma endscop
}
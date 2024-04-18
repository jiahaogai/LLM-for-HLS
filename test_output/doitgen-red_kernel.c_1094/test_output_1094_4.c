#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int alpha,int beta,int tmp[20][24],int A[20][30],int B[30][24])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 24; j++) {
      tmp[i][j] = ((long )0);
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{30}
    for (k = 0; k < 30; k++) {
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L3}
      for (j = 0; j < 24; j++) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    for (j = 0; j < 30; j++) {
      A[i][j] = beta * A[i][j] + sum_tmp;
    }
  }
//#pragma endscop
}
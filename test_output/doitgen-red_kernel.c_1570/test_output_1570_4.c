#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int alpha,int beta,double C[20][30],double A[20][40],double B[40][30])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 30; j++) {
      C[i][j] = ((double )0);
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 40; k++) {
      for (j = 0; j < 30; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}
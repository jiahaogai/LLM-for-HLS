#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int alpha,int beta,double C4[40][50],double A[40][60],double B[60][50])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{25}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      C4[i][j] = ((double )0);
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (k = 0; k < 30; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (j = 0; j < 50; j++) {
        C4[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}
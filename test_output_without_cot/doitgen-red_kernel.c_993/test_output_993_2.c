#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,double A[40][50][60],double B[40][50][80],double C[50][60][80],double D[80][60][90])
{
  int r_i;
  int r_j;
  int r_k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r_i = 0; r_i < 40; r_i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (r_j = 0; r_j < 50; r_j++) {
      for (r_k = 0; r_k < 60; r_k++) {
        A[r_i][r_j][r_k] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r_i = 0; r_i < 40; r_i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (r_j = 0; r_j < 50; r_j++) {
      for (r_k = 0; r_k < 80; r_k++) {
        double sum = 0.0;
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
        for (int i = 0; i < 60; i++) {
          sum += A[i][r_j][r_k] * B[i][r_j][r_k];
        }
        A[r_i][r_j][r_k] = sum;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r_i = 0; r_i < 50; r_i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (r_j = 0; r_j < 60; r_j++) {
      for (r_k = 0; r_k < 90; r_k++) {
        double sum = 0.0;
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        for (r_l = 0; r_l < 80; r_l++) {
          sum += A[r_l][r_i][r_k] * C[r_l][r_j][r_k];
        }
        D[r_i][r_j][r_k] = sum;
      }
    }
  }
//#pragma endscop
}
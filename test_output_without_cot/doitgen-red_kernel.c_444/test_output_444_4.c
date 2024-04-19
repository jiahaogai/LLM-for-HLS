#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,double A[25][20][30],double B[20][25][30],double C[30][30][nl],double D[30][25][nl])
{
  int r_i;
  int r_j;
  int r_k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{25}
  for (r_i = 0; r_i < 25; r_i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (r_j = 0; r_j < 20; r_j++) {
      for (r_k = 0; r_k < 30; r_k++) {
        A[r_i][r_j][r_k] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r_i = 0; r_i < 30; r_i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (r_j = 0; r_j < 30; r_j++) {
      for (r_k = 0; r_k < 25; r_k++) {
        C[r_i][r_j][r_k] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r_i = 0; r_i < 25; r_i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (r_j = 0; r_j < 30; r_j++) {
      for (r_k = 0; r_k < 20; r_k++) {
        for (r_l = 0; r_l < 30; r_l++) {
          A[r_i][r_k][r_l] += B[r_k][r_i][r_j] * D[r_l][r_k][r_j];
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r_i = 0; r_i < 30; r_i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (r_j = 0; r_j < 30; r_j++) {
      for (r_k = 0; r_k < 25; r_k++) {
        C[r_i][r_j][r_k] += A[r_k][r_i][r_j];
      }
    }
  }
//#pragma endscop
}
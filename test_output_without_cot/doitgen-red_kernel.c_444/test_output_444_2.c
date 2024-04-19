#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,double A[25][20][30],double B[25][30][40],double C[30][40][50],double D[20][40][50])
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
    for (r_j = 0; r_j < 30; r_j++) {
      for (r_k = 0; r_k < 40; r_k++) {
        A[r_i][0][r_k] = 0.0;
        for (int i = 0; i < 20; i++) {
          A[r_i][i][r_k] += D[i][r_j][r_k] * B[r_i][r_j][r_k];
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r_i = 0; r_i < 30; r_i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (r_j = 0; r_j < 40; r_j++) {
      for (r_k = 0; r_k < 50; r_k++) {
        C[r_i][r_j][0] = 0.0;
        for (int i = 0; i < 25; i++) {
          C[r_i][r_j][r_k] += A[i][r_j][r_k] * B[i][r_j][r_k];
        }
      }
    }
  }
//#pragma endscop
}
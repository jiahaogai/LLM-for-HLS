#pragma ACCEL kernel

void kernel_3mm(int ni,int nj,int nk,int nl,int nm,double E[40][50],double A[40][60],double B[60][50],double F[50][70],double C[50][80],double D[80][70],double G[40][70])
{
  int i;
  int j;
  int k;
//#pragma scop
/* E := E */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      E[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (k = 0; k < 60; ++k) {
        E[i][j] += A[i][k] * B[k][j];
      }
    }
  }
/* F := F + E*C */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 70; j++) {
      F[i][j] += E[i][0] * C[0][j];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 1; k < 50; ++k) {
        F[i][j] += E[i][k] * C[k][j];
      }
    }
  }
/* D := D + F*D */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 70; j++) {
      D[i][j] += F[i][0] * D[0][j];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 1; k < 70; ++k) {
        D[i][j] += F[i][k] * D[k][j];
      }
    }
  }
/* G := C*D */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      G[i][j] = C[i][0] * D[0][j];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 1; k < 70; ++k) {
        G[i][j] += C[i][k] * D[k][j];
      }
    }
  }
//#pragma endscop
}
#pragma ACCEL kernel

void kernel_3mm(int ni,int nj,int nk,int nl,int nm,double E[40][50],double A[40][30],double B[30][40],double F[40][20],double C[20][50],double D[50][40],double G[40][20])
{
  int i;
  int j;
  int k;
//#pragma scop
/* E := A*B */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      E[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 30; ++k) {
        E[i][j] += A[i][k] * B[k][j];
      }
    }
  }
/* F := C*D */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{20}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 20; j++) {
      F[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 50; ++k) {
        F[i][j] += C[k][i] * D[k][j];
      }
    }
  }
/* G := E*F */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 20; j++) {
      G[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 50; ++k) {
        G[i][j] += E[i][k] * F[k][j];
      }
    }
  }
//#pragma endscop
}
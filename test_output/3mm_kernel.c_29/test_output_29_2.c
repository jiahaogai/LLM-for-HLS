#pragma ACCEL kernel

void kernel_3mm(int ni,int nj,int nk,int nl,int nm,double E[40][50],double A[40][60],double B[60][70],double F[70][80],double C[50][80],double D[40][80],double G[40][50])
{
  int i;
  int j;
  int k;
//#pragma scop
/* E */
  for (i = 0; i < 40; i++) {
    for (j = 0; j < 50; j++) {
      E[i][j] = 0.0;
      for (k = 0; k < 60; k++) {
        E[i][j] += A[i][k] * B[k][j];
      }
    }
  }
/* F */
  for (i = 0; i < 40; i++) {
    for (j = 0; j < 80; j++) {
      F[i][j] = 0.0;
      for (k = 0; k < 70; k++) {
        F[i][j] += C[k][j] * D[i][k];
      }
    }
  }
/* G */
  for (i = 0; i < 40; i++) {
    for (j = 0; j < 50; j++) {
      G[i][j] = 0.0;
      for (k = 0; k < 60; k++) {
        G[i][j] += E[i][k] * F[k][j];
      }
    }
  }
//#pragma endscop
}
#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400][400],double v1[400][400],double u2[400][400],double v2[400][400],double x[400][400],double y[400][400],double z[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      A[i][j] += + u1[i][0] * v1[j][0] + u1[i][1] * v1[j][1] + u1[i][2] * v1[j][2] + u1[i][3] * v1[j][3] + u1[i][4] * v1[j][4] + u1[i][5] * v1[j][5] + u1[i][6] * v1[j][6] + u1[i][7] * v1[j][7] + u1[i][8] * v1[j][8];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      x[i][j] +=  + 0.0 * (A[j][0] * v2[i][0] + A[j][1] * v2[i][1] + A[j][2] * v2[i][2] + A[j][3] * v2[i][3] + A[j][4] * v2[i][4] + A[j][5] * v2[i][5] + A[j][6] * v2[i][6] + A[j][7] * v2[i][7] + A[j][8] * v2[i][8]);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L6}
    for (j = 0; j < 400; j++) {
      y[i][j] +=  + 1.0 * (u2[j][0] * x[i][0] + u2[j][1] * x[i][1] + u2[j][2] * x[i][2] + u2[j][3] * x[i][3] + u2[j][4] * x[i][4] + u2[j][5] * x[i][5] + u2[j][6] * x[i][6] + u2[j][7] * x[i][7] + u2[j][8] * x[i][8]);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=z FACTOR=auto{__PARA__L7}
    for (j = 0; j < 400; j++) {
      z[i][j] +=  + alpha * (y[i][0] * v1[j][0] + y[i][1] * v1[j][1] + y[i][2] * v1[j][2] + y[i][3] * v1[j][3] + y[i][4] * v1[j][4] + y[i][5] * v1[j][5] + y[i][6] * v1[j][6] + y[i][7] * v1[j][7] + y[i][8] * v1[j][8] + y[i][9] * v1[j][9] + y[i][10] * v1[j][10] + y[i][11] * v1[j][11] + y[i][12] * v1[j][12] + y[i][13] * v1[j][13] + y[i][14] * v1[j][14] + y[i][15] * v1[j][15] + y[i][16] * v1[j][16] + y[i][17] * v1[j][17] + y[i][18] * v1[j][18] + y[i][19] * v1[j][19] + y[i][20] * v1[j][20] + y[i][21] * v1[j][21] + y[i][22] * v1[j][22] + y[i][23] * v1[j][23] + y[i][24] * v1[j][24] + y[i][25] * v1[j][25] + y[i][26] * v1[j][26] + y[i][27] * v1[j][27] + y[i][28] * v1[j][28] + y[i][29] * v1[j][29] + y[i][30] * v1[j][30] + y[i][31] * v1[j][31] + y[i][32] * v1[j][32] + y[i][33] * v1[j][33] + y[i][34] * v1[j][34] + y[i][35] * v1[j][35] + y[i][36] * v1[j][36] + y[i][37] * v1[j][37] + y[i][38] * v1[j][38] + y[i][39] * v1[j][39]);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=w FACTOR=auto{__PARA__L9}
    for (j = 0; j < 400; j++) {
      w[i][j] +=  + beta * A[i][j];
    }
  }
}
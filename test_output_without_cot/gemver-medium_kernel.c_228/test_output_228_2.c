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
      x[i][j] +=  + v2[i][0] * A[j][0] + v2[i][1] * A[j][1] + v2[i][2] * A[j][2] + v2[i][3] * A[j][3] + v2[i][4] * A[j][4] + v2[i][5] * A[j][5] + v2[i][6] * A[j][6] + v2[i][7] * A[j][7] + v2[i][8] * A[j][8];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L6}
    for (j = 0; j < 400; j++) {
      y[i][j] +=  + u2[i][0] * x[j][0] + u2[i][1] * x[j][1] + u2[i][2] * x[j][2] + u2[i][3] * x[j][3] + u2[i][4] * x[j][4] + u2[i][5] * x[j][5] + u2[i][6] * x[j][6] + u2[i][7] * x[j][7] + u2[i][8] * x[j][8];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=z FACTOR=auto{__PARA__L7}
    for (j = 0; j < 400; j++) {
      z[i][j] +=  alpha * y[i][j] + beta * z[i][j];
    }
  }
}
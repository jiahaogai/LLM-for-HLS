#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400][400],double v1[400][400],double u2[400][400],double v2[400][400],double w[400][400],double x[400][400],double y[400][400],double z[400][400])
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
      x[i][j] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (j = 0; j < 400; j++) {
      x[i][j] += beta * y[i][j] * A[j][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=z FACTOR=auto{__PARA__L7}
    for (j = 0; j < 400; j++) {
      z[i][j] = z[i][j] + alpha * A[i][j] * x[j][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=w FACTOR=auto{__PARA__L8}
    for (j = 0; j < 400; j++) {
      w[i][j] = beta * w[i][j] + u2[i][0] * v2[j][0] + u2[i][1] * v2[j][1] + u2[i][2] * v2[j][2] + u2[i][3] * v2[j][3] + u2[i][4] * v2[j][4] + u2[i][5] * v2[j][5] + u2[i][6] * v2[j][6] + u2[i][7] * v2[j][7] + u2[i][8] * v2[j][8];
    }
  }
}
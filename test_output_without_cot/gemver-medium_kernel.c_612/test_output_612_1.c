- '#pragma ACCEL PARALLEL reduction=x FACTOR=auto{32}': Perform parallel reduction for the specified variable 'x', with a factor of 32 determined automatically.
- '#pragma ACCEL PARALLEL reduction=y FACTOR=auto{32}': Perform parallel reduction for the specified variable 'y', with a factor of 32 determined automatically.
- '#pragma ACCEL PARALLEL reduction=z FACTOR=auto{32}': Perform parallel reduction for the specified variable 'z', with a factor of 32 determined automatically.

#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x[i] = ((double )0);
    y[i] = ((double )0);
    z[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 400; i++) {
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double tmp_z = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp_x FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      tmp_x += A[i][j] * x[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp_y FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      tmp_y += A[i][j] * y[j];
    }
    
#pragma ACCEL PARALLEL reduction=tmp_z FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      tmp_z += A[i][j] * z[j];
    }
    x[i] = tmp_x + alpha * x[i] + beta * y[i];
    y[i] = tmp_y + alpha * y[i] + beta * z[i];
    z[i] = tmp_z + alpha * z[i];
  }
}
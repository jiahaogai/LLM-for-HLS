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
    
#pragma ACCEL PARALLEL reduction=w FACTOR=auto{32}
    for (j = 0; j < 400; j++) {
      w[i] += beta * A[j][i] * x[j];
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    x[i] = y[i] + z[i] * w[i];
  }
}
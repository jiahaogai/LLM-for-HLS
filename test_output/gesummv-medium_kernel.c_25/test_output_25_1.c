#pragma ACCEL kernel

void kernel_gesummv(double alpha,double beta,double A[250][250],double B[250][250],double tmp[250],double x[250],double y[250])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 250; i++) {
    tmp[i] = ((double )0);
    y[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 250; j++) {
      tmp[i] += A[i][j] * x[j];
      y[i] += B[i][j] * x[j];
    }
    y[i] = alpha * tmp[i] + beta * y[i];
  }
}
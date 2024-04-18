#pragma ACCEL kernel

void kernel_atax(double A[390][410],double x[410],double y[410],double tmp[390])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 410; i++) {
    tmp[0] = A[0][i] * x[i];
  }
  tmp[0] = ((double )0);
  
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L1}
  for (i = 0; i < 390; i++) {
    tmp[0] += (double )A[i][0] * y[0];
  }
  y[0] = tmp[0];
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 410; i++) {
    y[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L3}
    for (j = 0; j < 390; j++) {
      y[i] += A[j][i] * tmp[j];
    }
  }
}
#pragma ACCEL kernel

void kernel_atax(double A[390][410],double x[410],double y[410],double tmp[390])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 410; i++) {
    tmp[0] += x[i] * A[0][i];
  }
  
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{32}
  for (i = 0; i < 390; i++) {
    y[i] = tmp[i];
    tmp[i] = 0.0;
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 0; j < 410; j++) {
      tmp[i] += x[j] * A[i][j];
    }
  }
  
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L3}
  for (i = 0; i < 410; i++) {
    y[i] = y[i] + tmp[0];
  }
}
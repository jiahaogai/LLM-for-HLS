#pragma ACCEL kernel

void kernel_atax(double A[390][410],double x[410],double y[410],double tmp[390])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 410; i++) {
    tmp[0] = A[0][i] * x[i];
  }
  
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{2}
  for (i = 0; i < 410; i++) {
    y[i] = tmp[0];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 320; i++) {
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L3}
    for (j = 0; j < 410; j++) {
      y[j] += A[i][j] * x[i];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  for (i = 0; i < 390; i++) {
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L6}
    for (j = 0; j < 410; j++) {
      tmp[i] += A[i][j] * y[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L8}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
  for (i = 0; i < 410; i++) {
    x[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{__PARA__L9}
    for (j = 0; j < 390; j++) {
      x[i] += A[j][i] * tmp[j];
    }
  }
}
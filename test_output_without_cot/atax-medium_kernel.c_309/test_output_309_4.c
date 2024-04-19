#pragma ACCEL kernel

void kernel_atax(double A[390][410],double x[410],double y[410],double tmp[390])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 410; i++) {
    tmp[0] = x[i] * A[0][i];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 32; i++) {
    tmp[i + 1] = tmp[i] + x[i + 1] * A[i + 1][409];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 32; i < 409; i++) {
    tmp[i] = tmp[i - 32] + x[i + 1] * A[409][i];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 410; i++) {
    y[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (i = 0; i < 390; i++) {
    j = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (j = 0; j < 410; j++) {
      y[j] += A[i][j] * tmp[i];
    }
  }
}
 
 #pragma ACCEL kernel

void kernel_mvt(double x[120], double y[120], double u1[120], double u2[120], double v1[120], double v2[120], int n)
{
  int i;
  int j;
  double tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 120; i++) {
    tmp = (x[i] * u1[i] + y[i] * v1[i]) ;
    v2[i] = (x[i] * u2[i] + y[i] * v2[i]) ;
    u2[i] = tmp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 120; i++) {
    y[i] = u2[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 120; i++) {
    v1[i] = u1[i] + v2[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (i = 0; i < 120; i++) {
    x[i] = u1[i] + v1[i];
  }
}

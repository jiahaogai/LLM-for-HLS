
 #pragma ACCEL kernel

void kernel_mvt(double x[400],double y[400],double u1[400],double u2[400],double v[400],int n)
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    x[i] = 1.0;
    y[i] = 1.0;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=u1 FACTOR=auto{__PARA__L50}
    for (j = 0; j < 400; j++) {
      u1[i] += x[j] * v[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L30}
    for (j = 0; j < 400; j++) {
      y[i] += u1[j] * u2[j];
    }
  }
}
- '#pragma ACCEL PIPELINE auto{__PIPE__L2}': PIPELINE auto{__PIPE__L2}
- '#pragma ACCEL TILE FACTOR=auto{__TILE__L2}': TILE FACTOR=auto{__TILE__L2}
- '#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}': PARALLEL FACTOR=auto{__PARA__L2}
- '#pragma ACCEL PARALLEL reduction=v2 FACTOR=auto{__PARA__L3}': PARALLEL reduction FACTOR=auto{__PARA__L3}
- '#pragma ACCEL PARALLEL reduction=u1 FACTOR=auto{__PARA__L4}': PARALLEL reduction FACTOR=auto{__PARA__L4}
- '#pragma ACCEL PIPELINE auto{__PIPE__L5}': PIPELINE auto{__PIPE__L5}
- '#pragma ACCEL TILE FACTOR=auto{__TILE__L5}': TILE FACTOR=auto{__TILE__L5}
- '#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}': PARALLEL FACTOR=auto{__PARA__L5}
- '#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L6}': PARALLEL reduction FACTOR=auto{__PARA__L6}
- '#pragma ACCEL PIPELINE auto{__PIPE__L7}': PIPELINE auto{__PIPE__L7}
- '#pragma ACCEL TILE FACTOR=auto{__TILE__L7}': TILE FACTOR=auto{__TILE__L7}
- '#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}': PARALLEL FACTOR=auto{__PARA__L7}
- '#pragma ACCEL PARALLEL reduction=z FACTOR=auto{__PARA__L8}': PARALLEL reduction FACTOR=auto{__PARA__L8}
- '#pragma ACCEL PIPELINE auto{__PIPE__L9}': PIPELINE auto{__PIPE__L9}
- '#pragma ACCEL TILE FACTOR=auto{__TILE__L9}': TILE FACTOR=auto{__TILE__L9}
- '#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}': PARALLEL FACTOR=auto{__PARA__L9}
- '#pragma ACCEL PARALLEL reduction=v1 FACTOR=auto{__PARA__L10}': PARALLEL reduction FACTOR=auto{__PARA__L10}
- '#pragma ACCEL PARALLEL reduction=u2 FACTOR=auto{__PARA__L11}': PARALLEL reduction FACTOR=auto{__PARA__L11}
 
#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{8}
    for (j = 0; j < 400; j++) {
      x[i] += beta * A[j][i] * y[j];
    }
  }
  
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x[i] = x[i] + z[i];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=w FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      w[i] += alpha * A[i][j] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=v2 FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      v2[i] += A[j][i] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=u1 FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      u1[i] += A[i][j] * y[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      y[i] += alpha * A[i][j] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=v1 FACTOR=auto{__PARA__L6}
    for (j = 0; j < 400; j++) {
      v1[i] += A[j][i] * x[j
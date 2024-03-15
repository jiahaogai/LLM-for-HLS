
 #pragma ACCEL kernel

void kernel_big(int tsteps,int n,double u[60][60],double v[60][60],double w[60][60],double x[60][60],double y[60][60],double z[60][60])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      for (j = 1; j < 59; j++) {
        u[i][j] = 1.0 / ((1.0 + ((double )(i * j))) * (1.0 + ((double )(i * j))));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 1; j < 59; j++) {
        v[i][j] = 1.0 / ((1.0 + ((double )(i * j))) * (1.0 + ((double )(i * j))));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (j = 1; j < 59; j++) {
        w[i][j] = 1.0 / ((1.0 + ((double )(i * j))) * (1.0 + ((double )(i * j))));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L8}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
      for (j = 1; j < 59; j++) {
        x[i][j] = ((double )(i * j)) / ((((double )(1 + i)) * (1.0 + ((double )(i * j)))));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L10}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L10}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L11}
      for (j = 1; j < 59; j++) {
        y[i][j] = ((double )(i * j)) / ((((double )(1 + j)) * (1.0 + ((double )(i * j)))));
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L12}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L12}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L12}
    for (i = 1; i < 59; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L13}
      for (j = 1; j < 59; j++) {
        z[i][j] = ((double )(4.0 - (i * (j + 1.0)))) / ((((double )(1 + i)) * (1.0 + ((double )(i * j)))));
      }
    }
  }
}

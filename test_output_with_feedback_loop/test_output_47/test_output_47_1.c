#pragma ACCEL kernel

void kernel_bicg(int m,int n,double A[410][390],double s[390],double q[410],double p[390],double r[410])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 390; i++) {
    s[i] = ((double )0);
    q[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 410; i++) {
    q[0] += r[i] * A[i][0];
    s[0] += r[i] * A[i][0];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 390; i++) {
    p[i] = q[i] / s[0];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (i = 0; i < 410; i++) {
    int _in_j;
    _in_j = 0;
    j = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (j = 0; j < 390; j++) {
      q[j] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    for (j = 0; j < 390; j++) {
      q[ _in_j ] += r[i] * A[i][j];
      s[ _in_j ] += r[i] * A[i][j];
      _in_j = j;
    }
  }
}

7. Turn off automatic parallelization for the following loop.
8. Mark the following loop as FAST_FOURIER_TRANSFORM
9. Mark the following loop as FAST_WALSH_TRANSFORM
10. Turn off automatic parallelization for the following loop.
11. Mark the following loop as FAST_WALSH_TRANSFORM
 
#pragma ACCEL kernel

void kernel_atax(double A[390][410],double x[410],double y[410],double tmp[390])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 410; i++) {
    tmp[0] = 0.0;
    x[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{30}
    for (j = 0; j < 390; j++) {
      tmp[0] += A[j][i] * x[j];
      y[i] += A[j][i] * x[j];
    }
    x[i] = x[i] + 1.0e+00 * tmp[0] * 4.0e-50;
  }
}

void kernel_bicg(int m,int n,double A[90][90],double s[90],double q[90],double p[90],double r[90],double d[90],double tmp[90])
{
  int i;
  int k;
  int j;
  int k_col;
  double tmp_sum;
  double tmp_x_q;
  double s_q;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 90; i++) {
    s[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 90; i++) {
    tmp_sum = ((double )0);
    
#pragma ACCEL PARALLEL reduction=tmp_sum FACTOR=auto{__PARA__L5}
    for (k = 0; k < 90; k++) {
      tmp_sum += A[i][k] * d[k];
    }
    s[i] = tmp_sum;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 90; i++) {
    q[i] = s[i] / r[i];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (i = 0; i < 90; i++) {
    tmp_x_q = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp_x_q FACTOR=auto{__PARA__L6}
    for (k = 0; k < 90; k++) {
      k_col = (int )A[k][i];
      tmp_x_q += A[k][i] * q[k_col];
    }
    p[i] = s[i] + tmp_x_q;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L7}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  for (i = 0; i < 90; i++) {
    s_q = 0.0;
    
#pragma ACCEL PARALLEL reduction=s_q FACTOR=auto{__PARA__L8}
    for (k = 0; k < 90; k++) {
      s_q += A[i][k] * q[k];
    }
    tmp[i] = s_q;
    q[i] = r[i] * q[i];
  }
}

void kernel_bicg_2(int m,int n,double A[90][90],double s[90],double q[90],double p[90],double r[90],double d[90],double tmp[90])
{
  int i;
  int k;
  int j;
  int k_col;
  double tmp_sum;
  double tmp_x_q;
  double s_q;
  
#pragma ACCEL PIPELINE auto{__PIPE__L9}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
  for (i = 0; i < 90; i++) {
    s[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L10}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L10}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
  for (i = 0; i < 90; i++) {
    tmp_sum = ((double )0);
    
#pragma ACCEL PARALLEL reduction=tmp_sum FACTOR=auto{__PARA__L11}
    for (k = 0; k < 90; k++) {
      tmp_sum += A[i][k] * d[k];
    }
    s[i] = tmp_sum;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L12}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L12}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L12}
  for (i = 0; i < 90; i++) {
    q[i] = s[i] / r[i];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L13}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L13}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L13}
  for (i = 0; i < 90; i++) {
    tmp_x_q = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp_x_q FACTOR=auto{__PARA__L14}
    for (k = 0; k < 90; k++) {
      k_col = (int )A[k][i];
      tmp_x_q += A[k][i] * q[k_col];
    }
    p[i] = s[i] + tmp_x_q;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L15}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L15}
  
#pragma ACCEL PARALLEL FACT
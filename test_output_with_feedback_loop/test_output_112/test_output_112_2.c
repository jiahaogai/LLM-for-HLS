#pragma ACCEL kernel

void kernel_bicg(int m,int n,double A[410][390],double s[390],double q[410],double p[390],double r[410])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 390; i++) {
    s[i] = ((double )0);
    q[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 410; i++) {
    q[0] += r[i] * A[i][0];
    s[0] += r[i] * A[i][0];
    _intrinsic_vsev(((double *)q) + 0, 0, 2);
    _intrinsic_vsw(0, 2, ((double *)s) + 0, 0);
    double p_i = -1.0 * p[0];
    double r_i = ((double )0);
    
#pragma ACCEL PARALLEL reduction=r_i FACTOR=auto{1}
    for (j = 0; j < 390; j++) {
      r_i += s[j] * A[i][j];
    }
    q[0] = q[0] - r_i * p_i;
    _intrinsic_vld(((double *)s) + 0, 0, 2);
    _intrinsic_vld(((double *)q) + 0, 0, 2);
    _intrinsic_vadd2(r_i,p_i,0,2);
    double sum = r_i;
    r[i] = sum;
  }
}
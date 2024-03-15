#pragma ACCEL kernel

void kernel_bicg(int m,int n,double A[410][390],double s[390],double q[410],double p[390],double r[410])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 390; i++) {
    s[i] = ((double )0);
    q[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 410; i++) {
    q[0] += r[i] * A[i][0];
    s[0] += r[i] * A[i][0];
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 390; j++) {
      q[j] += r[i] * A[i][j];
      s[j] += A[i][j] * p[j];
    }
  }
}
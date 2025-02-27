#pragma ACCEL kernel

void kernel_bicg(int m,int n,double A[410][390],double s[390],double q[410],double p[390],double r[410])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{26472144}
  for (i = 0; i < 390; i++) {
    s[i] = ((double )0);
    q[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 410; i++) {
    q[0] += r[i] * A[i][0];
    s[0] += r[i] * A[i][0];
/* Multiply Q<j> by A<i,j> in A */
    
#pragma ACCEL PARALLEL FACTOR=auto{256}
    for (j = 0; j < 390; j++) {
      q[j] = q[j] * A[i][0] + r[i] * A[i][j];
      s[j] = s[j] * A[i][0] + p[i] * A[i][j];
    }
  }
}

 
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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 410; i++) {
    q[0] += r[i] * A[i][0];
    s[0] += r[i] * A[i][0];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 390; i++) {
    p[i] = -q[i] / s[0];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 410; i++) {
    int jj_limit = 0;
    int jj_upperbound = min(390, 1 + 0L * L PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 410; i++) {
    int jj_limit = 1;
    int jj_upperbound = 390;
    int jj_stride = 1;
    int jj_init = 0;
    int jj;
    jj = jj_init;
    jj_no_pipeline: 
#pragma ACCEL PIPELINE auto{off}
    jj_no_tile: 
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (j = 0; j < 390; j++) {
      s[j] += r[i] * A[i][j];
    }
  }
}

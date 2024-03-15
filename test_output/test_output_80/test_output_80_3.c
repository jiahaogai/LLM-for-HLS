
 
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
    int jj_buf = 0;
    jj_buf = 0;
    jj_limit = ((jj_buf + BLIS_JC_USE_BUF) <= JC_DIM);
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (j = 0; j < 390; j++) {
      int ii_limit = 0;
      int ii_buf = 0;
      ii_buf = 0;
      ii_limit = ((ii_buf + BLIS_IC_USE_BUF) <= IC_DIM);
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (jj = jj_buf; jj < ((jj_buf + BLIS_JC_USE_BUF) < JC_DIM ? BLIS_JC_USE_BUF : JC_DIM); jj++) {
        int _in_i = i;
        int _in_j = j;
        int _in_jj = jj;
        s[jj] += r[i] * A[_in_i][_in_j];
        q[i] += A[_in_i][_in_j] * p[_in_j];
      }
    }
  }
}

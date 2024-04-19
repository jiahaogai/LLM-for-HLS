#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i <= 57; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (j = 1; j <= 57; j++) {
        vt = v[i][j] - ((((p[i][j] + p[i][j + 1]) + p[i][j - 1]) + p[i + 1][j]) + p[i - 1][j]) / 4.0;
        up = u[i][j] - ((((vt[i][j] + vt[i][j + 1]) + vt[i][j - 1]) + vt[i + 1][j]) + vt[i - 1][j]) / 4.0;
        p[i][j] = 0.0;
        q[i][j] = 0.0;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 1; i <= 57; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 1; j <= 57; j++) {
        v[i][j] = v[i][j] - ((((q[i][j] + q[i][j + 1]) + q[i][j - 1]) + q[i + 1][j]) + q[i - 1][j]) / 4.0;
        u[i][j] = u[i][j] - ((((vt[i][j] + vt[i][j + 1]) + vt[i][j - 1]) + vt[i + 1][j]) + vt[i - 1][j]) / 4.0;
      }
    }
  }
}
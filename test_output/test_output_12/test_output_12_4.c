
 #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  for (tj = 1;tj < 42;tj++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (tk = 1;tk < 42;tk++) {
      
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{__PARA__L4}
      for (i = 1;i < 240;i++) {
        bv = dt * (xr[i] - x[tj]);
        bw = dt * (xr[i] - x[tk]);
        tmp2 = bv * bw;
        a = A[i][j][tk] + A[i][j][tj];
        tmp1 = A[i][j][tk] * bw + A[i][j][tj] * bv;
        C[i][j] += tmp2 * a;
        D[i][j] += tmp2 * tmp1;
        F[i][j] += tmp1 * bv;
        G[i][j] += tmp1 * bw;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{24}
    for (i = 1;i < 240;i++) {
      b = B[i][j];
      tmp1 = B[i][j] * F[i][j];
      e = E[i][j] + G[i][j];
      f = F[i][j] + B[i][j] * G[i][j];
      
#pragma ACCEL PARALLEL reduction=C[i][j] FACTOR=auto{__PARA__L5}
      for (ii = 1;ii < 240;ii++) {
        C[i][j] += B[i][ii] * E[i][ii];
      }
      D[i][j] = D[i][j] + tmp1 + e;
      C[i][j] = C[i][j] + b * e;
      F[i][j] = F[i][j] * b;
      G[i][j] = G[i][j] * b;
      E[i][j] = b * e;
      B[i][j] = b * f;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  for (i = 1;i < 240;i++) {
    for (j = 1;j < 240;j++) {
      q[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  for (i = 1;i < 240;i++) {
    for (j = 1;j < 240;j++) {
      P[i][j] = C[i][j] - D[i][j];
      Q[i][j] = P[i][j] / ((double )(2.0 * 41));
      r[i][j] = Q[i][j] - G[i][j];
      s[i][j] = F[i][j] - B[i][j] * r[i][j];
      double _tmp_ = s[i][j];
      for (k = 1;k < 240;k++) {
        q[i][k] += _tmp_ * B[k][j];
      }
    }
    double _tmp_ = 1.0e-4;
    for (k = 1;k < 240;k++) {
      q[i][k] = q[i][k] * _tmp_;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L8}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
  for (i = 1;i < 240;i++) {
    for (j = 1;j < 240;j++) {
      xr[i] += (( q[i][j] + r[i][j]) * x[j]);
    }
  }
}

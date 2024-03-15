
 #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  
#pragma ACCEL PIPELINE auto{__PIPE__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL reduction=u FACTOR=auto{__PARA__L2}
    for (i = 1; i < 39; i++) {
      b = 0.16666666666666666666666666L * f(i - 1);
      u[i] = u[i] + su[i] * (h * (p[i] - b - u[i] - q[i]));
    }
    
#pragma ACCEL PARALLEL reduction=q FACTOR=auto{__PARA__L3}
    for (i = 0; i < 39; i++) {
      q[i] = g[i] * u[i + 1] + h * (p[i] - q[i]);
    }
  }
}

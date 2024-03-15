#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  
#pragma ACCEL PIPELINE auto{__PIPE__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL reduction=u FACTOR=auto{__PARA__L2}
    for (i = 1; i < 39; i++) {
      u[i] = 0.33 * u[i] + 0.33 * v[i] + 0.33 * (q[i] - p[i] * u[i]);
    }
    
#pragma ACCEL PARALLEL reduction=v FACTOR=auto{__PARA__L3}
    for (i = 0; i < 39; i++) {
      v[i] = - 1.0 * v[i] + 1.0 * u[i] + 1.0 * (p[i + 1] - p[i]) / (e[i + 1] - d[i]) * (u[i + 1] - u[i]);
    }
  }
}

 #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  
#pragma ACCEL PIPELINE auto{__PIPE__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL reduction=u FACTOR=auto{__PARA__L2}
    for (i = 1; i < 92; i++) {
      b = sin(a);
      u[i] = u[i] + b * v[i] + p[i];
    }
    
#pragma ACCEL PARALLEL reduction=v FACTOR=auto{__PARA__L3}
    for (i = 0; i < 92; i++) {
      b = u[i] - v[i];
      y = i * (i - 1) * (i - 2);
      v[i] = v[i] + b * a * y;
    }
    
#pragma ACCEL PARALLEL reduction=p FACTOR=auto{__PARA__L4}
    for (i = 0; i < 92; i++) {
      d = 1.0 + a * (y - v[i]) - b * u[i];
      p[i] = d * p[i];
    }
  }
}


 #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  
#pragma ACCEL PIPELINE auto{__PIPE__L0}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 1; i < 39; i++) {
      b[i] = 0.0;
      s[i] = 0.0;
      q[i] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (i = 0; i < 39; i++) {
      y = _in_[i];
      s[i] = y;
      for (j = 1; j <= 39; j++) {
        b[j] += y * d[i * 39 + j];
      }
      q[i] = b[i] / b[i * 39 + i];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
    for (i = 0; i < 39; i++) {
      y = s[i];
      q_1m_1 = q[i - 1];
      x = y - q[i] * (b[i] - (q_1m_1) * b[i - 1]);
      d[i] = x;
    }
  }
}

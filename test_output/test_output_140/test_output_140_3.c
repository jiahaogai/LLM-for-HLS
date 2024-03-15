  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 1; t <= 30; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i <= 120; i++) {
      b[i] = 0.0;
      si = s[i] ;
      b[i] = b[i] + a[i] * si;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (i = 1; i <= 120; i++) {
      _in_ = a[i];
      _i_ = i;
      _j_ = seidel_L2[0][_i_];
      b[_j_] = b[_j_] + _in_ * gi;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 1; i <= 120; i++) {
      _in_ = b[i];
      _i_ = i;
      _j_ = seidel_L1[0][_i_];
      a[_j_] = a[_j_] + _in_ * gj;
    }
  }
}

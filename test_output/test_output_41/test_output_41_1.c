
 #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
  for (j = 1; j < 128; j++) {
    tmp = _in[j];
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 256; i++) {
      double col_j = _in[i * 128 + j];
      
      _out[i * 128 + j] = (tmp + col_j);
    }
  }
}

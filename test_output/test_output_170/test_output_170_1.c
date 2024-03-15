
  #pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (j = 16; j < 96; j++) {
    
#pragma ACCEL PARALLEL reduction=u FACTOR=auto{__PARA__L3}
    for (i = 16; i < 96; i++) {
      r1 = (double )0;
      r2 = (double )0;
      for (k = 16; k < 96; k++) {
        r1 += A[i * 96 + k] * B[k * 96 + j];
        r2 += A[i * 96 + k] * B[k * 96 + j];
      }
      Q1[i * 96 + j] = r1;
      Q2[i * 96 + j] = r2;
    }
  }
}

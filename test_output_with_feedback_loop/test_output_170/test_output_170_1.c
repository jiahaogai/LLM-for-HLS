#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 16; i < 96; i++) {
    dm2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{__PARA__L4}
    for (j = 16; j < 96; j++) {
      dm2[i] += dm1[j] * b[i * j];
    }
  }
}
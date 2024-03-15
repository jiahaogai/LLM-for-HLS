  \n");
  for (t = 0; t < 30; t++) {
    float suml = 0.0;
    float sumi = 0.0;
    
#pragma ACCEL PIPELINE auto{__PIPE__L0}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L0}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PARALLEL reduction=suml FACTOR=auto{__PARA__L4}
      for (i = 0; i < 50; i++) {
        suml += A[i + j * (50)][t];
      }
      
#pragma ACCEL PARALLEL reduction=sumi FACTOR=auto{__PARA__L5}
      for (i = 0; i < 50; i++) {
        sumi += B[i + j * (50)][t] * suml;
      }
    }
    C[t] = sumi;
  }
}

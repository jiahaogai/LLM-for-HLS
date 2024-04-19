#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{1}


#pragma ACCEL PARALLEL FACTOR=auto{1}
  
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{1}
  for(i = 0; i < 400; i++) {
    tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for(j = 0; j < 400; j++) {
      tmp += A[i][j] * y_1[j];
    }
    x1[i] = tmp;
  }

#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}


#pragma ACCEL PARALLEL FACTOR=auto{10}
  
#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{12}
  for(i = 0; i < 400; i++) {
    tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L2}
    for(j = 0; j < 400; j++) {
      tmp += A[i][j] * y_2[j];
    }
    x2[i] = tmp;
  }
}
### ACCEL PIPELINE auto{flatten}

### ACCEL TILE FACTOR=auto{1}
 
#pragma ACCEL PARALLEL FACTOR=auto{2}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}

  for(i = 0; i < 400; i++) {
    tmp1 = 0.0;
    tmp2 = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{12}
    for(j = 0; j < 400; j++) {
      tmp1 += A[i][j] * y_1[j];
      tmp2 += A[i][j] * y_2[j];
    }
	x1[i] = tmp1;
	x2[i] = tmp2;
  }
}
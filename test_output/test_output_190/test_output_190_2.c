

  sum = m[0];
  float tmp = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (tile = 1; tile < 8; tile++) {
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
    for (i = 0; i < 200; i++) {
      sum = sum + m[i * 8 + tile];
    }
    tmp = sum;
    sum = tmp + 1.0;
    sum = tmp + 2.0;
  }
}

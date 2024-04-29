#pragma ACCEL PIPELINE auto{off}
  #pragma ACCEL TILE FACTOR=auto{4}
   #pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8192; i++) 
   sol[i] = 0.0;
  
#pragma ACCEL PIPELINE auto{off}
  #pragma ACCEL TILE FACTOR=auto{4}
   #pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8192; i++) {
    tmp = 0.0;
    for (j = 0; j < 9; j++) {
      tmp += filter[j] * orig[i + (-4 + j)];
    }
    sol[i] = tmp;
  }
}
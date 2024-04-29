Code: ### Algorithm:
  for (i = 1; i < 8190; i++) {
    orig[i] = ((2 * orig[i - 1]) + (2 * orig[i + 1]) + orig[i + 2] +
     orig[i - 2]) / 4;
  }
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8190; i++) {
    sol[i] = ((2 * sol[i - 1]) + (2 * sol[i + 1]) + sol[i + 2] +
      sol[i - 2]) / 4;
  }
//#pragma endscop
}
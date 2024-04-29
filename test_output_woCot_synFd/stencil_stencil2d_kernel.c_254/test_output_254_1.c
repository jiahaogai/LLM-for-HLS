Code: #pragma ACCEL PIPELINE auto{off}

 #pragma ACCEL TILE FACTOR=auto{1}

 #pragma ACCEL PARALLEL FACTOR=auto{1}

outer:
for (i = 0; i < 256; i++) {
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  middle:
  for (j = 0; j < 256; j++) {
    s = 0.0;
    inner:
    for (k = 0; k < 9; k++) {
      idx = (256 + 1 + 8) * (k - 4) + i * (256 + 1 + 0) + j;
      s += ((double )filter[k]) * orig[idx];
    }
    sol[i * 256 + j] = s;
  }
}
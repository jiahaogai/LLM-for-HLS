#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    orig[i] = i;
  }
  
#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sol[i] = ((filter[0] * orig[i]) + (filter[1] * orig[i + 1]) + (filter[2] * orig[i + 2]) + (filter[3] * orig[i + 8]) + (filter[4] * orig[i + 9]) + (filter[5] * orig[i + 10]) + (filter[6] * orig[i + 11]) + (filter[7] * orig[i + 12]) + (filter[8] * orig[i + 16])) >> 4;
  }
}
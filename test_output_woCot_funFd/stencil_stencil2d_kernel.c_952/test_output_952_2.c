Code: #pragma ACCEL PIPELINE auto{off}
 #pragma ACCEL TILE FACTOR=auto{1}
 #pragma ACCEL PARALLEL FACTOR=auto{3}
for (i = 0; i < 8192; i++) {
  sol[i] = ((filter[0] * orig[i]) + (filter[1] * orig[i + 1]) + (filter[2] * orig[i + 2])) + ((filter[3] * orig[i + 3]) + (filter[4] * orig[i + 4]) + (filter[5] * orig[i + 5])) + ((filter[6] * orig[i + 6]) + (filter[7] * orig[i + 7]) + (filter[8] * orig[i + 8]));
}
#pragma ACCEL PIPELINE auto{flatten}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 0; i < 8192; i++) {
  orig[i] = sol[i];
}
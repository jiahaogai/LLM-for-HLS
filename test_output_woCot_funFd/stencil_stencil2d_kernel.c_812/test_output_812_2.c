Code: #pragma ACCEL PIPELINE auto{flatten}
#pragma ACCEL TILE FACTOR=auto{2}
#pragma ACCEL PARALLEL FACTOR=auto{31}
   for (i = 1; i < 32 - 1; i++) {
      for (j = 1; j < 32 - 1; j++) {
         sum = 0.0;
         idx = 0;
         while (idx < 9) {
            sum += filter[idx] * orig[((i + idx - 1) % 32) * 32 + ((j + idx - 1) % 32)];
            idx++;
         }
         sol[i * 32 + j] = sum;
      }
   }
#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
   for (i = 1; i < 32 - 1; i++) {
      for (j = 1; j < 32 - 1; j++) {
         idx = (i * 32) + j;
         orig[idx] = sol[idx];
      }
   }
}
Code: #pragma ACCEL PIPELINE auto{flatten}
 #pragma ACCEL TILE FACTOR=auto{2}
 #pragma ACCEL PARALLEL FACTOR=auto{31}
   for (r = 1; r < 32 - 1; r++) {
      for (q = 1; q < 32 - 1; q++) {
         val = orig[r * 32 + q] * filter[0];
         sum = val;
         sp = r * 32 + q + 1;
         sq = 1;
         for (qs = 1; qs < 9; qs++) {
            sum += orig[sp + sq * 32] * filter[qs];
            sq++;
         }
         sp = r * 32 + q - 1;
         sq = 1;
         for (qs = 1; qs < 9; qs++) {
            sum += orig[sp + sq * 32] * filter[qs];
            sq++;
         }
         sol[r * 32 + q] = sum;
      }
   }
}
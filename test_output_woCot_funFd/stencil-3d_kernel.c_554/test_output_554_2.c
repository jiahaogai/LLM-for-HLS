<<<<<<< HEAD
Code: #pragma ACCEL kernel
=======
Code: #pragma ACCEL PIPELINE auto{off}`:
   - Explanation: Prevent the automatic pipelining of the outer loop.
8. `#pragma ACCEL TILE FACTOR=auto{1}`:
   - Explanation: Keep the outer loop whole, without dividing it into smaller parts.
9. `#pragma ACCEL PIPELINE auto{}`:
   - Explanation: Allow automatic pipelining for the inner loop.
10. `#pragma ACCEL TILE FACTOR=auto{2}`:
     - Explanation: Divide the inner loop into smaller parts with a factor of 2.
11. `#pragma ACCEL PIPELINE auto{off}`:
     - Explanation: Prevent the automatic pipelining of the stencil.
12. `#pragma ACCEL TILE FACTOR=auto{1}`:
     - Explanation: Keep the stencil whole, without dividing it into smaller parts.
13. `#pragma ACCEL PIPELINE auto{flatten}`:
     - Explanation: Flatten the application of the stencil.
14. `#pragma ACCEL PIPELINE auto{off}`:
     - Explanation: Prevent the automatic pipelining of the update.
15. `#pragma ACCEL TILE FACTOR=auto{1}`:
     - Explanation: Keep the update whole, without dividing it into smaller parts.
16. `#pragma ACCEL PIPELINE auto{off}`:
     - Explanation: Prevent the automatic pipelining of the outer loop.
17. `#pragma ACCEL TILE FACTOR=auto{1}`:
     - Explanation: Keep the outer loop whole, without dividing it into smaller parts.
18. `#pragma ACCEL PIPELINE auto{off}`:
     - Explanation: Prevent the automatic pipelining of the inner loop.
19. `#pragma ACCEL TILE FACTOR=auto{2}`:
     - Explanation: Divide the inner loop into smaller parts with a factor of 2.
20. `#pragma ACCEL PIPELINE auto{off}`:
     - Explanation: Prevent the automatic pipelining of the stencil.
21. `#pragma ACCEL TILE FACTOR=auto{1}`:
     - Explanation: Keep the stencil whole, without dividing it into smaller parts.
22. `#pragma ACCEL PIPELINE auto{off}`:
     - Explanation: Prevent the automatic pipelining of the update.
23. `#pragma ACCEL TILE FACTOR=auto{1}`:
     - Explanation: Keep the update whole, without dividing it into smaller parts.


#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
<<<<<<< HEAD
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long idx_pad;
  long t;
=======
  long idx;
  long s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k <= 40 + 0 - 1; k++) {
     k_col = k;
     k_row = 40 + 0 - k - 1;
     idx_pad = k_col + ((40 + 0 - 1) * k_row);
     loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j <= 40 + 0 - 1; j++) {
      j_col = j;
      j_row = 40 + 0 - j - 1;
      idx_col = j_col + 0;
      idx_row = j_row + 40 * 1;
      idx = idx_pad + 40 * idx_row;
      loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i <= 40 + 0 - 1; i++) {
        i_col = i;
        i_row = 40 + 0 - i - 1;
        t = orig[idx_col + 40 * idx_row] + ((+1.0 * (orig[idx_col + 40 * (idx_row - 1)] + orig[idx_col + 40 * (idx_row + 1)])) + (+1.0 * (orig[idx_col - 1 + 40 * idx_row] + orig[idx_col + 1 + 40 * idx_row])));
        sol[idx] = ((-2.0 * 1) * orig[idx]) + (1.0 * t);
        idx_col = i_col + 0;
        idx_row = i_row + 40 * 1;
        idx = idx_pad + 40 * idx_row;
      }
      idx_row = j_row + 40 * 0;
      idx = idx_pad + 40 * idx_row;
    }
    idx_pad = k_col + ((40 + 0 - 1) * (40 + 0 - 1));
    loop_j_pad:
/* Standardize from: for(j = 40 - 1; j >= 1; j--) {...} */
    for (j = 40 + 0 - 1; j >= 1 + 0; j--) {
      j_col = 40 + 0 - j - 1;
      j_row = j;
      idx_col = j_col + 0;
      idx_row = j_row + 40 * 1;
      idx = idx_pad + 40 * idx_row;
      loop_i_pad:
/* Standardize from: for(i = 40 - 1; i >= 1; i--) {...} */
      for (i = 40 + 0 - 1; i >= 1 + 0; i--) {
        i_col = 40 + 0 - i - 1;
        i_row = i;
        idx_col = i_col + 0;
        idx_row = i_row + 40 * 1;
        idx = idx_pad + 40 * idx_row;
        sol[idx]
=======
  loopk:
  for (k = 0; k < 32; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
    for (j = 0; j < 32; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 0; i < 32; i++) {
        idx = i + j * 32 + k * 32 * 32;
        s = orig[idx] + ((0 + 0 * 32) * orig[idx - 1 - 32 * 32] + (0 + 1 * 32) * orig[idx + 1 - 32 * 32] + (0 + 0 * 32) * orig[idx - 32 - 32 * 32] + (0
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

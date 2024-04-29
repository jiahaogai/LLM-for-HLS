Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long NX;
  long NY;
  long NZ;
  long P;
  long Q;
  long R;
  long pad;
  long M;
  long total_threads;
  long thread_idx;
  long thread_id;
  long tj;
  long tk;
  long shx;
  long shy;
  long shz;
  long bx;
  long by;
  long bz;
  long jj;
  long kk;
  long idx_start;
  long idx_end;
  long idx_step;
  long t;
  long x;
  long y;
  long z;
  long v;
//#pragma scop
  pad = 1;
  NX = 32 + 2 * pad;
  NY = 32 + 2 * pad;
  NZ = 32 + 2 * pad;
  P = 2;
  Q = 2;
  R = 2;
  M = NX - 1;
  shx = 1;
  shy = NX - 1;
  shz = NX * (NY - 1);
  bx = 32 / shx;
  by = 1;
  bz = 1;
  total_threads = bx * by * bz;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 0; i < 39304; i++) {
    orig[i] = ((long )((double )(1 << 18) * ((double )rand() / ((double )RAND_MAX + 1.0))));
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  thread_idx = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  loop_j:
  for (j = 0; j < 32; j++) {
    loop_k:
    for (k = 0; k < 32; k++) {
      loop_t:
      for (t = 0; t < 4; t++) {
        v = 0;
        idx_start = ((pad + 1) + (j * (NY - 2 * pad)) + ((k * (NZ - 2 * pad)) * NY));
        idx_end = (idx_start - 1) + M;
        idx_step = NY - 2 * pad;
        loop_x:
        for (x = 0; x < 32; x += 8) {
          shx = 1;
          if (x == 32 - 8) {
            shx = 1 - (M - 1) % 8;
          }
          loop_y:
          for (y = 0; y < shx; y++) {
            v += C0 * ((((((orig[idx_end - 1] + orig[idx_end]) + orig[idx_end + 1]) + orig[idx_end + 2]) + orig[idx_end + 3]) + orig[idx_end + 4]) + orig[idx_end + 5]) + C1 * ((((((orig[idx_end - 2] + orig[idx_end - 1]) + orig[idx_end]) + orig[idx_end + 1]) + orig[idx_end + 2]) + orig[idx_end + 3]) + orig[idx_end + 4]);
            idx_end += NY - 2 * pad;
          }
        }
        sol[thread_idx] = v;
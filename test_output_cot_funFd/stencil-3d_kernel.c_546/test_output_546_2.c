Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long s;
  long P;
  long Q;
  long R;
  long C0P1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  P = 32L;
  Q = 32L;
  R = 32L;
  C0P1 = C0 + 1L;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
  for (k = 0L; k < R; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 0L; j < Q; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
      for (i = 0L; i < P; i++) {
        idx = i + j * P + k * Q * P;
        s = C0P1 * (orig[idx] + ((-1L) * (orig[idx + C0P1] + orig[idx + C0]))) + C1 * (orig[idx + C0P1] + orig[idx + C0]);
        sol[idx] = s / (1L + 2L * C1);
      }
    }
  }
}
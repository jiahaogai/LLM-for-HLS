Code: ### Parameters:

   - C0

   - C1

   - orig

   - sol

### Local Variables:
   - N0

   - N1

   - N2

   - i0

   - i1

   - i2

   - pad0

   - pad1

   - pad2

   - pad3

   - n_pad

   - i_pad

   - j_pad

   - k_pad

   - k

   - j

   - i

   - t

   - x

   - y

   - z

   - tmp

### Function Body:
 #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long N0;
  long N1;
  long N2;
  long i0;
  long i1;
  long i2;
  long pad0;
  long pad1;
  long pad2;
  long pad3;
  long n_pad;
  long i_pad;
  long j_pad;
  long k_pad;
  long k;
  long j;
  long i;
  long t;
  long x;
  long y;
  long z;
  long tmp;
  N0 = 4L;
  N1 = 4L;
  N2 = 4L;
  pad0 = 1L;
  pad1 = 1L;
  pad2 = 1L;
  pad3 = 1L;
  n_pad = N0 + pad0 + pad1;
  t = (pad0 << 1) + N0;
  x = (pad1 << 1) + N1;
  y = (pad2 << 1) + N2;
  z = t * x * y;
  i_pad = pad0 + N0;
  j_pad = pad1 + N1;
  k_pad = pad2 + N2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i0:
  for (i0 = 0L; i0 < 4L; i0++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{4}
    loop_i1:
    for (i1 = 0L; i1 < 4L; i1++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i2:
      for (i2 = 0L; i2 < 4L; i2++) {
        loop_k:
        for (k = 0L; k < 4L; k++) {
          loop_j:
          for (j = 0L; j < 4L; j++) {
            loop_i:
            for (i = 0L; i < 4L; i++) {
              tmp = ((pad0 + i) * t + pad1 + j) * y + pad2 + k;
              sol[tmp] = ((C0 * (orig[tmp - n_pad - y - z] - orig[tmp - n_pad - z])) + (C1 * (orig[tmp - n_pad - y] - orig[tmp - n_pad]))) + ((C0 * (orig[tmp - n_pad + y - z] - orig[tmp - n_pad + z])) + (C1 * (orig[tmp - n_pad + y] - orig[tmp - n_pad])));
            }
          }
        }
      }
    }
  }
}
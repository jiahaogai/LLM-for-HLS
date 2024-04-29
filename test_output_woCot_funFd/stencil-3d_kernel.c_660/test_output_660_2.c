#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 2; k < 392; k++) {...} */
  for (k = 2 + 299; k <= 392 + 299; k += 299) {
    k_col = k - 2;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 2; j < 392; j++) {...} */
    for (j = 2 + 299; j <= 392 + 299; j += 299) {
      j_col = j - 2;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 392; i++) {...} */
      for (i = 2 + 1; i <= 392 + 1; i += 1) {
        i_col = i - 2;
        sum = ((C0 * orig[i + ((j + 0 * 299) * 392) + ((k + 0 * 299) * 39304)]) + (C1 * (orig[i + ((j + 1 * 299) * 392)] + orig[i + ((j - 1 * 299) * 392)]))) + (orig[i + ((j + 0 * 299) * 392) + ((k + 1 * 299) * 39304)]);
        sum += (C1 * (orig[i + ((j + 2 * 299) * 392)] + orig[i + ((j - 2 * 299) * 392)])) ;
        sum += (C1 * (orig[i + ((j + 1 * 299) * 392) + ((k - 1 * 299) * 39304)] + orig[i + ((j - 1 * 299) * 392) + ((k - 1 * 299) * 39304)])) ;
        sum += (orig[i + ((j + 0 * 299) * 392) + ((k - 1 * 299) * 39304)]) ;
        buf[0] = sum;
        sum = ((C0 * buf[1]) + (C1 * (buf[2] + buf[0]))) + buf[3];
        sum += (C1 * (buf[5] + buf[4])) ;
        sum += (C1 * (buf[6] + buf[7]));
        sum += buf[8];
        sol[i + ((j + 0 * 299) * 392) + ((k + 0 * 299) * 39304)] = sum;
      }
    }
  }
}
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
  loopk:
/* Standardize from: for(k = 2; k < 39302; k++) {...} */
  for (k = 2 + 0; k < 39302 + 0; k += 27) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    loopj:
/* Standardize from: for(j = 2; j < 39302; j++) {...} */
    for (j = 2 + 0; j < 39302 + 0; j += 27) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 2; i < 39302; i++) {...} */
      for (i = 2 + 0; i < 39302 + 0; i += 27) {
        sum = 0;
        buf[0] = orig[i + 2 + 39304 * (j + 2 + 39304 * (k + 2))];
        buf[1] = orig[i + 3 + 39304 * (j + 2 + 39304 * (k + 2))];
        buf[2] = orig[i + 4 + 39304 * (j + 2 + 39304 * (k + 2))];
        buf[3] = orig[i + 39304 * (j + 2 + 39304 * (k + 2))];
        buf[4] = orig[i + 39304 * (j + 3 + 39304 * (k + 2))];
        buf[5] = orig[i + 39304 * (j + 4 + 39304 * (k + 2))];
        buf[6] = orig[i + 39304 * (j + 39304 * (k + 2))];
        buf[7] = orig[i + 39304 * (j + 39304 * (k + 3))];
        buf[8] = orig[i + 39304 * (j + 39304 * (k + 4))];
        k_col = 2;
        loopk_col:
        while (k_col < 27) {
          j_col = 2;
          loopj_col:
          while (j_col < 27) {
            i_col = 2;
            loopi_col:
            while (i_col < 27) {
              sum += buf[k_col * 9 + j_col * 3 + i_col] * C0;
              i_col++;
            }
            sum += buf[k_col * 9 + j_col * 3 + 4] * C1;
            j_col++;
          }
          sum += buf[k_col * 9 + 4] * C1;
          k_col++;
        }
        sum += buf[4] * C1;
        sol[i + 39304 * (j + 39304 * k)] = sum;
      }
    }
  }
}
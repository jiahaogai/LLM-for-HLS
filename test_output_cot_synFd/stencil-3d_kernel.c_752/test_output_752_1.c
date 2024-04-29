#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long _in_;
  long _out_;
  _in_ = 0L;
  _out_ = 32768L;
  outer:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1L + _in_; i < 33L + _in_; i++) {
    middle:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
    for (j = 1L + _in_; j < 33L + _in_; j++) {
      inner:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
      for (k = 1L + _in_; k < 33L + _in_; k++) {
        idx = i * 90L + j * 3L + k;
        sol[idx] = ((C0 * (orig[idx - 1 - 3296L] + orig[idx + 1 + 3296L])) + (C1 * (orig[idx - 3296L] + orig[idx + 3296L]))) / (C0 + C1);
      }
    }
  }
}
#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long pad;
  long pad_col;
  long tmp;
  long tmp_col;
  pad = 1;
  pad_col = 392;
  k_col = 0;
  i_col = pad_col + 1;
  tmp_col = 0;
  while (i_col < pad_col + 2) {
     tmp = 0;
     pad = tmp_col;
     tmp_col++;
     pad_col++;
     j = pad;
     while (j < pad + 392) {
        tmp = ((C0 * orig[j]) + (C1 * orig[j + 392]) + (orig[j + 393])) + tmp;
        j += 392;
     }
     sol[k_col] = tmp;
     k_col++;
     j = i_col;
     while (j < i_col + 392) {
        orig[j] = orig[j + 1];
        j += 392;
     }
     orig[i_col + 392 - 1] = 0;
     i_col++;
  }
}
#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  long tmp;
  long tmp_row;
  long tmp_cmd;
  long tmp_0;
  long tmp_1;
  long tmp_2;
  long tmp_3;
  long tmp_4;
  long tmp_5;
  long tmp_6;
  long tmp_7;
  long tmp_8;
  long tmp_9;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_k:
/* Standardize from: for(k = 2; k < 32 + 2; k++) {...} */
  for (k = 2; k <= 34; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
/* Standardize from: for(j = 2; j < 32 + 2; j++) {...} */
    for (j = 2; j <= 34; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 2; i < 32 + 2; i++) {...} */
      for (i = 2; i <= 34; i++) {
        tmp_row = ((k - 2) * 32 + (j - 2)) * 32 + (i - 2);
        tmp_0 = orig[tmp_row];
        tmp_1 = orig[tmp_row + 1];
        tmp_2 = orig[tmp_row + 2];
        tmp_3 = orig[tmp_row + 32];
        tmp_4 = orig[tmp_row + 33];
        tmp_5 = orig[tmp_row + 34];
        tmp_6 = orig[tmp_row + 32 + 1];
        tmp_7 = orig[tmp_row + 32 + 2];
        tmp_8 = orig[tmp_row + 32 + 3];
        tmp_9 = (orig[tmp_row + 1] + orig[tmp_row + 32] + orig[tmp_row + 32 + 1]) + 2L;
        tmp = ((orig[tmp_row + 32 + 3] + tmp_9) + orig[tmp_row + 34]) + 2L;
        buf = tmp_0;
        sol[tmp_row] = tmp;
      }
    }
  }
}
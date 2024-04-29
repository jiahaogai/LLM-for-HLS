#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long ko;
  long ji;
  long pi;
  long po;
  long ci;
  long di;
  long fi;
  long mi;
  long ri;
  long q;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_l1:
/* Standardize from: for(i = 1; i < 32; i++) {...} */
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_l2:
/* Standardize from: for(j = 1; j < 32; j++) {...} */
    for (j = 1; j < 33; j++) {
      loop_l3:
/* Standardize from: for(k = 1; k < 32; k++) {...} */
      for (k = 1; k < 33; k++) {
        k_col = 32 * k;
        j_col = 32 * j;
        i_col = 32 * i;
        q = k_col + j_col + i_col;
        ko = k_col - 1;
        ji = j_col - 1;
        pi = i_col - 1;
        po = k_col + 1;
        ci = j_col + 1;
        di = i_col + 1;
        fi = ki_32[k];
        mi = kj_32[j];
        ri = ki_j_32[k][j];
        loop_l4:
/* Standardize from: for(o = 0; o < 30; o++) {...} */
        for (o = 0; o < 30; o++) {
          sol[po] = ((C0 * sol[po]) + (C1 * ((orig[ri + o]) +
            ((filt[fi][0] * sol[ko]) + (filt[fi][1] * sol[ji]) +
            (filt[fi][2] * sol[pi]) + (filt[fi][3] * sol[ci]) +
            (filt[fi][4] * sol[di]) + (filt[fi][5] * sol[fi]))) +
            (filt[fi][6] * sol[ri])));
        }
      }
    }
  }
}
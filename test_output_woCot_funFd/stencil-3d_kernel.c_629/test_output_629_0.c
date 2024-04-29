#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  bound = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopk:
/* Standardize from: for(k = 2; k < 3928; k++) {...} */
  for (k = ((long )2) + bound; k < 3928L + bound; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 2; j < 3926; j++) {...} */
    for (j = ((long )2) + bound; j < 3926L + bound; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 2; i < 3924; i++) {...} */
      for (i = ((long )2) + bound; i < 3924L + bound; i++) {
        i_col = i - 2L;
        j_col = j - 2L;
        k_col = k - 2L;
        t1 = orig[i + ((j + ((k + 0L) * 3926) * 3924))];
        t2 = orig[i_col + ((j + ((k + 1L) * 3926) * 3924))];
        t3 = orig[i_col + ((j_col + ((k + 1L) * 3926) * 3924))];
        sol[i + ((j + ((k + 0L) * 3926) * 3924))];
      }
    }
  }
}
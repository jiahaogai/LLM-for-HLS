#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[250][250][2];
  long s;
  long t;
  long u;
  long v;
  long w;
  long p;
  long q;
  long r;
  long s_col;
  long t_col;
  long u_col;
  long v_col;
  long w_col;
  long pad_limit_i = 2;
  long pad_limit_j = 2;
  long pad_limit_k = 2;
  long pad_limit = 2;
  long col_limit_i = 39284;
  long col_limit_j = 250;
  long col_limit_k = 250;
  long col_limit = 39284;
  long row_limit_i = 2;
  long row_limit_j = 1;
  long row_limit_k = 1;
  long row_limit = 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj_pad:
/* Standardize from: for(j = 2; j < 252; j++) {...} */
  for (j = ((long )2) + pad_limit_j; j < 252 + pad_limit_j; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_pad:
/* Standardize from: for(k = 2; k < 252; k++) {...} */
    for (k = ((long )2) + pad_limit_k; k < 252 + pad_limit_k; k++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_pad:
/* Standardize from: for(i = 2; i < 39282; i++) {...} */
      for (i = ((long )2) + pad_limit_i; i < 39282 + pad_limit_i; i++) {
        s_col = ((((long )2) + pad_limit_j) - 1);
        t_col = ((((long )2) + pad_limit_k) - 1);
        u_col = ((((long )2) + pad_limit) - 1);
        v_col = ((((long )1) + pad_limit_j) - 1);
        w_col = ((((long )1) + pad_limit_k) - 1);
        buf[0][0][0] = orig[i + ((j - ((long )2)) * 39282) + ((k - ((long )2)) * 39284)];
        buf[0][0][1] = orig[i + s_col + ((j - ((long )2)) * 39282) + ((k - ((long )2)) * 39284)];
        buf[0][1][0] = orig[i + ((j - ((long )1)) * 39282) + ((k - ((long )2)) * 39284)];
        buf[0][1][1] = orig[i + s_col + ((j - ((long )1)) * 39282) + ((k - ((long )2)) * 39284)];
        buf[1][0][0] = orig[i + ((j - ((long )2)) * 39282) + ((k - ((long )1)) * 39284)];
        buf[1][0][1] = orig[i + s_col + ((j - ((long )2)) * 39282) + ((k - ((long )1)) * 39284)];
        buf[1][1][0] = orig[i + ((j - ((long )1)) * 39282) + ((k - ((long )1)) * 39284)];
        buf[1][1][1] = orig[i + s_col + ((j - ((long )1)) * 39282) + ((k - ((long )1)) * 39284)];
        i_col = 1;
        j_col = 2;
        k_col = 4;
        sp:
/* Standardize from: for( ; i_col < 250; i_col++) {...} */
        while (i_col < 250) {
          t = i_col + ((j - ((long )2)) * 250);
          p = i_col + ((k - ((long )2)) * 250);
          buf[0][j_col][0] = orig[t + ((j - ((long )2)) * 39282) + ((k - ((long )2)) * 39284)];
          buf[0][j_col][1] = orig[t + s_col + ((j - ((long )2)) * 39282) + ((k - ((long )2)) * 39284)];
          buf[1][j_col][0] = orig[t + ((j - ((long )1)) * 39282) + ((k - ((long )2)) * 39284)];
          buf[1][j_col][1] = orig[t + s_col + ((j - ((long )1)) * 39282) + ((k - ((long )2)) * 39284)];
          buf[2][j_col][0] = orig[t + ((j - ((long )2)) * 39282) + ((k - ((long )1)) * 39284)];
          buf[2][j_col][1] = orig[t + s_col + ((j - ((long )2)) * 39282) + ((k - ((long )1)) * 39284)];
          buf[3][j_col][0] = orig[t + ((j - ((long )1)) * 39282) + ((k - ((long )1)) * 39284)];
          buf[3][j_col][1] = orig[t + s_col + ((j - ((long )1)) * 39282) + ((k - ((long )1)) * 39284)];
          k_col = 1;
          sp_col:
/* Standardize from: for( ; k_col < 250; k_col++) {...} */
          while (k_col < 250) {
            v = p + k_col;
            w = v_col + k_col;
            q = p + w_col;
            sol[i + ((j - ((long )2)) * 39282) + ((k - ((long )2)) * 39284)] = (buf[0][0][0] + ((buf[0][0][1] - buf[0][1][0]) + (buf[1][0][0] + (buf[1][0][1] - buf[1][1][0]) - (buf[2][0][0] + buf[2][0][1] - buf[3][0][0] - buf[3][0][1]) + buf[3][1][0]))) + ((buf[0][1][0] + (buf[0][1][1] - buf[0][2][0]) - (buf[1][1][0] + buf[1][1][1] - buf[1][2][0] - buf[1][2][1]) + buf[2][1][0] + (buf[2][1][1] - buf[2][2][0] - buf[2][2][1]) - buf[3][1][0] - buf[3][1][1] + buf[3][2][0]));
          }
          k_col = 4;
        }
        i_col = 250;
      }
      j_col = 250;
    }
    k_col = 4;
  }
}
#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[25][25][25],long sol[25][25][25])
{
  long i;
  long j;
  long k;
  long ko;
  long kp;
  long jj;
  long jp;
  long ii;
  long ip;
  long mul0;
  long mul1;
  long sum0;
  long sum1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 25; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 25; k++) {
        ko = k - 1;
        if (ko < 0) {
          ko = 0;
        }
        kp = k + 1;
        if (kp > 24) {
          kp = 24;
        }
        jj = j - 1;
        if (jj < 0) {
          jj = 0;
        }
        jp = j + 1;
        if (jp > 24) {
          jp = 24;
        }
        ii = i - 1;
        if (ii < 0) {
          ii = 0;
        }
        ip = i + 1;
        if (ip > 24) {
          ip = 24;
        }
        sum0 = orig[i][j][k] + orig[ii][j][k] + orig[ip][j][k];
        sum0 += orig[i][jj][k] + orig[i][jp][k] + orig[i][j][ko] + orig[i][j][kp];
        sum1 = orig[ii][jj][k] + orig[ii][jp][k] + orig[ii][j][ko] + orig[ii][j][kp];
        sum1 += orig[ip][jj][k] + orig[ip][jp][k] + orig[ip][j][ko] + orig[ip][j][kp];
        mul0 = sum0 * C0;
        mul1 = sum1 * C1;
        sol[i][j][k] = mul0 + mul1;
      }
    }
  }
}
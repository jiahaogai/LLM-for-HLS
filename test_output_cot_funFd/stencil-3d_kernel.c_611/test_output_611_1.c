#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[25][25][25],long sol[25][25][25])
{
  long i;
  long j;
  long k;
  long ko;
  long ki;
  long kj;
  long i_col;
  long j_col;
  long k_col;
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  sum0 = 0;
  sum1 = 0;
  i_col = 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  j_col = 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  k_col = 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  ko = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (ko < 32) {
    ki = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    while (ki < 32) {
      kj = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      while (kj < 32) {
        i = ko + 1;
        j = ki + 1;
        k = kj + 1;
        sum0 = orig[i][j][k] + orig[i][j][k - 1] + orig[i][j][k + 1] + orig[i][j - 1][k] + orig[i][j + 1][k] + orig[i][j][k - 32] + orig[i][j][k + 32] + orig[i][j - 1][k - 32] + orig[i][j - 1][k + 32] + orig[i][j + 1][k - 32] + orig[i][j + 1][k + 32] + orig[i - 1][j][k] + orig[i - 1][j][k - 1] + orig[i - 1][j][k + 1] + orig[i - 1][j - 1][k] + orig[i - 1][j + 1][k] + orig[i - 1][j][k - 32] + orig[i - 1][j][k + 32] + orig[i - 1][j - 1][k - 32] + orig[i - 1][j - 1][k + 32] + orig[i - 1][j + 1][k - 32] + orig[i - 1][j + 1][k + 32] + orig[i + 1][j][k] + orig[i + 1][j][k - 1] + orig[i + 1][j][k + 1] + orig[i + 1][j - 1][k] + orig[i + 1][j + 1][k] + orig[i + 1][j][k - 32] + orig[i + 1][j][k + 32] + orig[i + 1][j - 1][k - 32] + orig[i + 1][j - 1][k + 32] + orig[i + 1][j + 1][k - 32] + orig[i + 1][j + 1][k + 32];
        sum1 = orig[i][j][k] * C0 + sum0 * C1;
        sol[i][j][k] = sum1;
        kj++;
      }
      ki++;
    }
    ko++;
  }
}
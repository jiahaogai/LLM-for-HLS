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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  j_col = 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  k_col = 2;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  i = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  j = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  k = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  ko = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  while (ko < 32) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    ki = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    while (ki < 32) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      kj = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      while (kj < 32) {
        sum0 = orig[i][j][k] + orig[i][j][ko] + orig[i][j][ki] + orig[i][j][k + 1] + orig[i][j][ko + 1] + orig[i][j][ki + 1] + orig[i][j][k - 1] + orig[i][j][ko - 1] + orig[i][j][ki - 1] + orig[i][j + 1][k] + orig[i][j + 1][ko] + orig[i][j + 1][ki] + orig[i][j + 1][k + 1] + orig[i][j + 1][ko + 1] + orig[i][j + 1][ki + 1] + orig[i][j + 1][k - 1] + orig[i][j + 1][ko - 1] + orig[i][j + 1][ki - 1] + orig[i][k][k] + orig[i][k][ko] + orig[i][k][ki] + orig[i][k][k + 1] + orig[i][k][ko + 1] + orig[i][k][ki + 1] + orig[i][k][k - 1] + orig[i][k][ko - 1] + orig[i][k][ki - 1] + orig[i][k - 1][k] + orig[i][k - 1][ko] + orig[i][k - 1][ki] + orig[i][k - 1][k + 1] + orig[i][k - 1][ko + 1] + orig[i][k - 1][ki + 1] + orig[i][k - 1][k - 1] + orig[i][k - 1][ko - 1] + orig[i][k - 1][ki - 1] + orig[i + 1][j][k] + orig[i + 1][j][ko] + orig[i + 1][j][ki] + orig[i + 1][j][k + 1] + orig[i + 1][j][ko + 1] + orig[i + 1][j][ki + 1] + orig[i + 1][j][k - 1] + orig[i + 1][j][ko - 1] + orig[i + 1][j][ki - 1] + orig[i + 1][j + 1][k] + orig[i + 1][j + 1][ko] + orig[i + 1][j + 1][ki] + orig[i + 1][j + 1][k + 1] + orig[i + 1][j + 1][ko + 1] + orig[i + 1][j + 1][ki + 1] + orig[i + 1][j + 1][k - 1] + orig[i + 1][j + 1][ko - 1] + orig[i + 1][j + 1][ki - 1] + orig[i + 1][k][k] + orig[i + 1][k][ko] + orig[i + 1][k][ki] + orig[i + 1][k][k + 1] + orig[i + 1][k][ko + 1] + orig[i + 1][k][ki + 1] + orig[i + 1][k][k - 1] + orig[i + 1][k][ko - 1] + orig[i + 1][k][ki - 1] + orig[i + 1][k - 1][k] + orig[i + 1][k - 1][ko] + orig[i + 1][k - 1][ki] + orig[i + 1][k - 1][k + 1] + orig[i + 1][k - 1][ko + 1] + orig[i + 1][k - 1][ki + 1] + orig[i + 1][k - 1][k - 1] + orig[i + 1][k - 1][ko - 1] + orig[i + 1][k - 1][ki - 1];
        mul0 = sum0 * C0;
        sum1 = mul0 + C1;
        mul1 = sum1 * C0;
        sol[i][j][k] = mul1;
        kj++;
      }
      ki++;
    }
    ko++;
  }
}
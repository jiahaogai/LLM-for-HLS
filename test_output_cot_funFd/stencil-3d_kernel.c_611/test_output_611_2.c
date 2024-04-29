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
  i_col = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (k = 0; k < 25; k++) {
     mul0 = orig[i_col][j_col][k] * C0;
     sum0 = sum0 + mul0;
  }
  i_col = 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (k = 0; k < 25; k++) {
     mul1 = orig[i_col][j_col][k] * C1;
     sum1 = sum1 + mul1;
  }
  i = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 25; j++) {
    j_col = 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 25; k++) {
      mul0 = orig[i][j_col][k] * C0;
      sum0 = sum0 + mul0;
    }
    j_col = 2;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 25; k++) {
      mul1 = orig[i][j_col][k] * C1;
      sum1 = sum1 + mul1;
    }
    k_col = 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 25 - 1; k++) {
      ko = 2 + k_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (ki = 2 + k_col; ki < 25 - k; ki++) {
        mul0 = orig[i][j][ko] * C0 + orig[i][j][ki] * C1;
        sum0 = sum0 + mul0;
      }
      k_col = k_col + 1;
    }
    ki = 25 - k_col;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for ( ; ki >= 3; ki--) {
      mul0 = orig[i][j][ki] * C0;
      sum0 = sum0 + mul0;
    }
    mul0 = orig[i][j][1] * C0;
    sum0 = sum0 + mul0;
    sol[i][j][k] = sum0;
  }
  j = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (k = 0; k < 25; k++) {
    k_col = 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (kj = 2 + k_col; kj < 25 - k; kj++) {
      mul1 = orig[i][kj][k] * C1;
      sum1 = sum1 + mul1;
    }
    k_col = k_col + 1;
  }
  ki = 25 - k_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for ( ; ki >= 3; ki--) {
    mul1 = orig[i][ki][k] * C1;
    sum1 = sum1 + mul1;
  }
  mul1 = orig[i][1][k] * C1;
  sum1 = sum1 + mul1;
  sol[i][j][k] = sum1;
}
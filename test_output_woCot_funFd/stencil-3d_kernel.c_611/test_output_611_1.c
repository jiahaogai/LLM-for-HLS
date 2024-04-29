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
    
#pragma ACCEL PARALLEL reduction=sum0 FACTOR=auto{2}
    for (j = 0; j < 25; j++) {
      
#pragma ACCEL PARALLEL reduction=sum0 FACTOR=auto{16}
      for (i = 0; i < 25; i++) {
        sum0 += orig[i][j][k];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  k_col = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (k = 0; k < 25 - 1; k++) {
    k_col = k_col << 1;
    ki = 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 25; j++) {
      
#pragma ACCEL PARALLEL reduction=sum1 FACTOR=auto{8}
      for (i = 0; i < 25 - 1; i++) {
        mul0 = ki * orig[i][j][k];
        sum1 += mul0;
        ki *= 2;
      }
      sol[i_col][j][k_col] = sum1;
      sum1 = 0;
      ki = 1;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  k_col = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (k = 0; k < 25 - 1; k++) {
    k_col = k_col << 1;
    ko = 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 25 - 1; j++) {
      j_col = j_col << 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = 0; i < 25 - 1; i++) {
        mul1 = ko * sol[i + 1][j][k_col];
        sum0 += mul1;
        mul1 = ki * sol[i][j + 1][k_col];
        sum0 += mul1;
        mul1 = kj * sol[i][j][k_col + 1];
        sum0 += mul1;
        ko *= 2;
        ki *= 2;
        kj *= 2;
      }
      sol[i_col][j][k_col] = sum0;
      sum0 = 0;
      ko = 1;
      ki = 1;
      kj = 1;
    }
  }
}
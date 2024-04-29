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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (k = 0; k < 25; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 25; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (i = 0; i < 25; i++) {
        sum0 = 0.0;
        sum1 = 0.0;
        mul0 = C0 * orig[k][j][i];
        sum0 += mul0;
        mul1 = C1 * orig[k][j][i];
        sum1 += mul1;
        sol[k][j][i] = sum0 + sum1;
      }
    }
  }
}
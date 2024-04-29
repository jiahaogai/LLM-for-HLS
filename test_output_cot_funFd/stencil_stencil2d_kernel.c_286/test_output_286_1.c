#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk:
/* Standardize from: for(k ... ) */
    for (k = 1; k < 33; k++) {
      i = (j - 1) * 32 + k - 1;
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      loopk2:
/* Standardize from: for(k ... ) */
      for (k = -1; k < 2; k++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loopj2:
/* Standardize from: for(j ... ) */
        for (j = -1; j < 2; j++) {
          sum += filter[((k + 1) * 3) + (j + 1)] * orig[i + (j * 32) + (k * 1)];
        }
      }
      sol[i] = sum;
    }
  }
}
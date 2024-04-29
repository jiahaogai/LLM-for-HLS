Code: #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
/* Standardize from: for(i ... ) */
    for (i = 1; i < 32; i++) {
      sum = 0.0;
      loopk:
/* Standardize from: for(k ... ) */
      for (k = 0; k < 9; k++) {
        row = i + ((k - 4) >> 2);
        col = j + ((k - 4) & 0x3);
        sum += filter[k] * orig[row * 32 + col];
      }
      sol[j * 32 + i] = sum;
    }
  }
}
#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{126}
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
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 1 + 0; j < 33 - 1 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loopk:
/* Standardize from: for(k = 1;k < 33 - 1;k++) {...} */
    for (k = 1 + 0; k < 33 - 1 + 0; k++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      looprow:
      for (row = 0; row < 33; row++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
        loopcol:
        for (col = 0; col < 33; col++) {
          sum += orig[row * 33 + col] * filter[k * 33 + col];
        }
      }
      sol[j * 33 + k] = sum;
    }
  }
}
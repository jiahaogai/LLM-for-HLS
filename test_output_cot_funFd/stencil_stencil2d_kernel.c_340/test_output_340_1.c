#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{126}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  loopj:
/* Standardize from: for(j = 1;j < 33 - 1;j++) {...} */
  for (j = 1 + 0; j < 33 - 1 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loopk:
    for (k = 1 + 0; k < 33 - 1 + 0; k++) {
      sum = 0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      looprow:
      for (row = -1 + 0; row < 2 + 0; row++) {
        
#pragma ACCEL PIPELINE auto{}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopcol:
        for (col = -1 + 0; col < 2 + 0; col++) {
          i = (0 + row) + (32 * (0 + col));
          sum += orig[i] * filter[col + 1 + (row + 1) * 3];
        }
      }
      sol[j + 32 * k] = sum;
    }
  }
}
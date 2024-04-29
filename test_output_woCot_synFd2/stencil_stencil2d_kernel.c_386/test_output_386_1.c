#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  loopj:
  for (j = 0; j < 64; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loopk:
    for (k = 0; k < 64; k++) {
      row = ((j + 0) * 64) + k;
      int sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      loopi:
      for (i = 0; i < 9; i++) {
        col = ((j + ((i - 4) + 0)) * 64) + ((k + ((i - 4) + 0)) + 0);
        sum += orig[col] * filter[i];
      }
      sol[row] = sum;
    }
  }
}
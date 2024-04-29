#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    inner:
    for (j = 0; j < 8; j++) {
      t = 0;
      row = i - 4;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      mid:
      for (col = j - 4; col <= j + 4; col++) {
        t += orig[row * 8 + col] * filter[mid - col];
      }
      sol[i * 8 + j] = t;
    }
  }
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  int flen;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  flen = 9;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  row = 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_row:
  for ( ; row < 128 - 1; row++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    col = 1;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    for ( ; col < 64 - 1; col++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_filter:
      for (j = 0; j < 9; j++) {
        i = row + (-4 + j);
        t += orig[i * 64 + col] * filter[j];
      }
      sol[row * 64 + col] = t;
    }
  }
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (row = -1; row <= 1; row++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        middle_inner:
        for (col = -1; col <= 1; col++) {
          t += filter[4 + row * 2 + col] * orig[i + row * 256 + col * 1];
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}
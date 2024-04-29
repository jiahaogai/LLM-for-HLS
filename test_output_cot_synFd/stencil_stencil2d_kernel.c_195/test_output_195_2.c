#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        x = i + ((k % 3) - 1);
        y = j + ((k / 3) - 1);
        if (((x >= 0) && (x < 256)) && ((y >= 0) && (y < 256))) {
          tmp += orig[x * 256 + y] * filter[k];
        }
      }
      sol[i * 256 + j] = tmp;
    }
  }
}
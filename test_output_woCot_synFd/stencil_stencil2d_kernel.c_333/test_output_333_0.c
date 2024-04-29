#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    inner:
    for (j = 0; j < 256; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_3:
      for (k = -4; k < 5; k++) {
        row = i + k;
        if (row < 0 || row > 255) {
          row = (row < 0 ? 0 : 255);
        }
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        inner_2:
        for (col = -4; col < 5; col++) {
          int x = row * 256 + (col < 0 ? col : 255);
          int y = (col < 0 ? -col : 510 - col);
          sum += orig[x] * filter[y];
        }
      }
      sol[i * 256 + j] = sum;
    }
  }
}
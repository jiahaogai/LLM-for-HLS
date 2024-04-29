#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k - 4) >> 5);
        col = j + ((k - 4) & 31);
        if ((((row >= 0)) && ((row < 8192))) && (((col >= 0)) && ((col < 8192)))) {
          sum += ((orig[row * 8192 + col] * filter[k])) ;
        }
      }
      sol[i * 8192 + j] = sum;
    }
  }
}
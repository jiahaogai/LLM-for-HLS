#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int sum;
  int row;
  int col;
=======
  int row;
  int col;
  int flatten_filter[81];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
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
=======
  for (i = 0; i < 81; i++) {
    flatten_filter[i] = filter[i];
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8; j++) {
      row = i - 1 + -40;
      col = j - 1 + -40;
      k = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      while (k < 9) {
        sol[row * 8 + col] += flatten_filter[k] * orig[row * 8 + col + k - 4];
        k++;
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
<<<<<<< HEAD
#pragma ACCEL kernel
=======
Code: #pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k1;
  int k2;
  int r;
  int c;
=======
  int k_col;
  int k_row;
  int row;
  int col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  int temp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
<<<<<<< HEAD
  for (r = 0; r < 128; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (c = 0; c < 64; c++) {
      temp = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k1 = 0; k1 < 3; k1++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k2 = 0; k2 < 3; k2++) {
          k = k1 * 3 + k2;
          temp += filter[k] * orig[r * 64 + c * 1 + k2];
        }
      }
      sol[r * 64 + c] = temp;
=======
  outer:
  for (row = 2; row < 128 - 2; row++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (col = 2; col < 64 - 2; col++) {
      temp = 0;
      inner:
      for (k_row = 0; k_row < 3; k_row++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_middle:
        for (k_col = 0; k_col < 3; k_col++) {
          k = (k_row * 3) + k_col;
          temp += filter[k] * orig[((row - 2) + k_row) * 64 + (col - 2) + k_col];
        }
      }
      sol[row * 64 + col] = temp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
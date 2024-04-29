<<<<<<< HEAD
=======
The error(s) occurred in the following function(s):
stencil



>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
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
  int result = 0;
//#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k / 3) - 1);
        col = j + ((k % 3) - 1);
        sum += filter[k] * orig[row * 256 + col];
      }
      sol[i * 256 + j] = sum;
    }
  }
=======
  for (i = 8; i < 8184 - 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8192 - 8; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + k - 4][j + k - 4];
      }
      sol[i][j] = result;
    }
  }
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}
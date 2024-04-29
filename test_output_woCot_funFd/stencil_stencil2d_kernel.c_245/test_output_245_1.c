<<<<<<< HEAD
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
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        row = i + ((k / 3) - 1);
        col = j + ((k % 3) - 1);
        if (((row < 0) || (row > 255)) || ((col < 0) || (col > 255))) {
          sum += 0;
        }
         else {
          sum += orig[row * 256 + col] * filter[k];
        }
      }
      sol[i * 256 + j] = sum;
    }
  }
}
=======
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error:
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

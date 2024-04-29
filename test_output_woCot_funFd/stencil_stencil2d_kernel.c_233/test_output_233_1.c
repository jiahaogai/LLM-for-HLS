Code: #pragma ACCEL kernel
<<<<<<< HEAD

=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int t;
  int row;
  int col;
=======
  int k;
  int result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loop_row:
  for (row = 1; row < 33; row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loop_col:
    for (col = 1; col < 33; col++) {
      t = 0;
      loop_elem:
      for (i = -1 + row; i <= 1 + row; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loop_inner_elem:
        for (j = -1 + col; j <= 1 + col; j++) {
          t += filter[((i + 1) * 3) + (j + 1)] * orig[i * 33 + j];
        }
      }
      sol[row * 33 + col] = t;
=======
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8176; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + (-4 + k) * 8192];
      }
      sol[i * 8192 + j] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
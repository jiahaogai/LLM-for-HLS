<<<<<<< HEAD
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int temp;
  int mul;
=======
Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int r;
  int r_col;
  int c;
  int c_col;
  int mul;
  int temp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
<<<<<<< HEAD
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (r = 2; r < 128 - 2; r++) {
=======
  loop:for (i = 0; i < 128 + 2; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
    
#pragma ACCEL PARALLEL FACTOR=auto{14}
    for (c = 2; c < 64 - 2; c++) {
      temp = 0;
      mul = 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k2 = 0; k2 < 9; k2++) {
        k1 = k2 + 1;
        temp += mul * orig[r * 64 + (c - 1 + 64) * 8 + k1];
        mul *= filter[k1];
      }
      sol[r * 64 + (c - 1 + 64) * 8] = temp;
=======
    loopj:for (j = 0; j < 64 + 2; j++) {
      r_col = i - 1;
      c_col = j - 1;
      temp = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopk:for (k = 0; k < 9; k++) {
        r = r_col + ((4 - 1) + (k / 3));
        c = c_col + ((4 - 1) + (k % 3));
        mul = orig[r * (64 + 2) + c] * filter[k];
        temp += mul;
      }
      sol[i * (64 + 2) + j] = temp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
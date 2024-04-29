#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(int orig[8192],int sol[8192],int filter[9])
=======
void stencil(double orig[8192],double sol[8192],double filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
=======
  int k_col;
  int k_row;
  double sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 8; k++) {
        result += filter[k] * orig[i + (-4 + k) * 8192];
      }
      sol[i * 8192 + j] = result;
    }
=======
  outer:
  for (i = 0; i < 8192; i++) {
    sum = 0.0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 9; j++) {
      k_col = i % 64;
      k_row = (i - k_col) / 64;
      k = ((k_row + 4) % 8) * 8 + (k_col + 4) % 8;
      sum += filter[j] * orig[k];
    }
    sol[i] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
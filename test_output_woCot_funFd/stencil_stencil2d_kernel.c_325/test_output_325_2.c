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
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      if (k < 0) {
        k = 0;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (j = 0; j < 9; j++) {
        k = i - 4 + j;
        if (k < 0) {
          k = 0;
        }
        if (k > 8191) {
          k = 8191;
        }
        result += ((int )filter[j]) * orig[k];
      }
    }
    sol[i] = result;
    result = 0;
=======
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((j + 4) - ((8 - 1) + ((k % 3) * 1)));
        k_row = ((i + 4) - ((8 - 1) + (((k / 3) + 1) * 1)));
        sum += filter[k] * orig[k_row * 8192 + k_col];
      }
      sol[i * 8192 + j] = sum;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
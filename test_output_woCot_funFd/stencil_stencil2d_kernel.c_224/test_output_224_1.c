#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(double orig[8192],double sol[8192],double filter[9])
=======
void stencil(int orig[8192],int sol[8192],int filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int k_row;
  double sum;
=======
  int tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8; i++) {
=======
  for (i = 0; i < 8192; i++) {
    tmp = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + ((k % 3) - 1);
        k_row = j + ((k / 3) - 1);
        if ((((k_col >= 0) && (k_col < 8)) && ((k_row >= 0) && (k_row < 8))) && (!((k == 4) && ((i == 0) || (i == 8))))) {
          sum += filter[k] * orig[k_row * 8 + k_col];
        }
      }
      sol[i * 8 + j] = sum;
    }
=======
    inner:
    for (j = 0; j < 9; j++) {
      tmp += filter[j] * orig[i + ((j - 4) << 12)];
    }
    sol[i] = tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
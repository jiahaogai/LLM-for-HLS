#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
<<<<<<< HEAD
  double mult;
=======
  double sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      mult = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{62}
      for (k_col = -4; k_col <= 4; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k_row = -4; k_row <= 4; k_row++) {
          k = k_row + 4 + (k_col << 3);
          mult += filter[k] * orig[i + k_row + 1 + ((j + k_col + 1) << 3)];
        }
      }
      sol[i + ((j << 3) + 1)] = mult;
=======
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 64; j++) {
      sum = 0.0;
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        k_row = i + (-4 + k_col);
        if ((((0 <= k_row) && (k_row < 64))) && (((0 <= j) && (j < 64)))) {
          k = k_row * 64 + j;
          sum += filter[k_col] * orig[k];
        }
      }
      sol[i * 64 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
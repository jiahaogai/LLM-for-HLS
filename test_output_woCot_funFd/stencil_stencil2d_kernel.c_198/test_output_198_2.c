#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  loopj:
  for (j = 1; j < 8191; j++) {
=======
  outer:
  for (i = 0; i < 8192; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
<<<<<<< HEAD
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
      loopk_row:
      for (k_row = 0 - (4 + (8 - 1)); k_row <= 4 - (8 + (8 - 1)); k_row++) {
        i = k_row + j;
        if (i < 0 || i > 8191) {
          continue;
        }
        k = k_col + 4 - (8 + (8 - 1));
        if (k < 0 || k > 8) {
          continue;
        }
        sum += filter[k] * orig[i * 8 + k];
      }
      sol[j * 8 + (k_col - 4 + (8 - 1))] = sum;
=======
    middle:
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((8192 == 1) ? 0 : i - 4 + ((8192 + 8 - 1) + (-4) * (8192 - 1)) * (k % 3));
        k_row = ((8192 == 1) ? 0 : j - 4 + ((8192 + 8 - 1) + (-4) * ((8192 - 1) - 1)) * (k / 3));
        sum += filter[k] * orig[k_row * 8192 + k_col];
      }
      sol[i * 8192 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
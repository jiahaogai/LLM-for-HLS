#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
=======
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int bound;
  bound = 8192 - 1;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
=======
  for (i = 1; i < bound - 1; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      inner:
      for (k = -4; k < 5; k++) {
        k_col = k + 4;
        i_col = i + k_col;
        if ((((i_col >= 0) && (i_col < 8192))) && (((j >= 0) && (j < 8192)))) {
          sum += filter[k + 4] * orig[i_col] * orig[j];
        }
      }
      sol[j] = sum;
=======
    for (j = 1; j < bound - 1; j++) {
      t = filter[0] * orig[i * bound + j - 1] + filter[1] * orig[i * bound + j] + filter[2] * orig[i * bound + j + 1] + filter[3] * orig[i * bound + j - bound] + filter[4] * orig[i * bound + j + bound] + filter[5] * orig[i * bound + j - 2 * bound] + filter[6] * orig[i * bound + j + 2 * bound] + filter[7] * orig[i * bound + j - 3 * bound] + filter[8] * orig[i * bound + j + 3 * bound];
      sol[i * bound + j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
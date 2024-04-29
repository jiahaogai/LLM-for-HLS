<<<<<<< HEAD
- Flatten the access to the `orig` array to improve cache utilization.
- Flatten the access to the `sol` array to improve cache utilization.

=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
=======
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8; i++) {
=======
  for (i = 0; i < 256; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i * 8 + j * 1 + k - 4];
      }
      sol[i * 8 + j] = result;
=======
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = -4; k < 5; k++) {
        idx = (256 + i + ((k + 4) * 256)) % 8192;
        val += filter[4 + k] * orig[idx];
      }
      sol[i * 256 + j] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
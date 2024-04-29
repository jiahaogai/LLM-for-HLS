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
  int s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
=======
  for (i = 0; i < 256; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8192; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{32}
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + k - 4 + ((j + k - 4) * 8192)];
      }
      sol[i * 8192 + j] = result;
=======
    for (j = 0; j < 256; j++) {
      s = 0;
      inner:
      for (k = -4; k < 5; k++) {
        idx = (256 + (i + k)) % 256;
        s += filter[4 + k] * orig[256 * idx + j];
      }
      sol[256 * i + j] = s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
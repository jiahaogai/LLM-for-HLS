#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int val;
=======
  int sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + orig[i + ((k - 4) % 256)]) % 256;
        val += filter[k] * orig[j + ((idx - 4) % 256)];
      }
      sol[i * 256 + j] = val;
=======
  for (i = 0; i < 8192; i++) {
     middle:
    for (j = 0; j < 8192; j++) {
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        sum += orig[i + ((k - 4) * 8192)] * filter[k];
      }
      sol[i * 8192 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
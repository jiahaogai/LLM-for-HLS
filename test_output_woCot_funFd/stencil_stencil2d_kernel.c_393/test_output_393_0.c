#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + i - 4) * 256 + (256 + j - 4) * 9 + k;
        val += orig[idx] * filter[k];
=======
    inner:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner_1:
      for (k = 0; k < 9; k++) {
        idx = (256 + orig[i + ((k - 4) % 256)]) % 256;
        val += filter[k] * orig[j + ((idx - 4) % 256)];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
      sol[i * 256 + j] = val;
    }
  }
}
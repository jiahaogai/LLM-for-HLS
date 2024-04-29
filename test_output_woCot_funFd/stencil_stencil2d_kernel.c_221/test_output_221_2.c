#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + orig[i + ((k - 4) << 8)] - filter[k]) % 256;
        val += idx * filter[k];
      }
      sol[i * 256 + j] = val;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx] + filter[0] * (orig[idx - 8192] + orig[idx + 8192]) + filter[1] * (orig[idx - 8191] + orig[idx + 8191]) + filter[2] * (orig[idx - 8190] + orig[idx + 8190]);
      sol[idx] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
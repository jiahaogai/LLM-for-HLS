#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{126}
#pragma ACCEL PARALLEL FACTOR=auto{1}

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + 1 + (-1 + k)) * 256 + 1 + (-1 + j);
        val += filter[k] * orig[idx];
      }
      sol[i * 256 + j] = val;
=======
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      result = ((0 * orig[i - 1 + (j - 1) * 8192]) + (0 * orig[i - 0 + (j - 1) * 8192]) + (0 * orig[i + 1 + (j - 1) * 8192]) + (0 * orig[i - 1 + (j - 0) * 8192]) + (1 * orig[i - 0 + (j - 0) * 8192]) + (0 * orig[i + 1 + (j - 0) * 8192]) + (0 * orig[i - 1 + (j + 1) * 8192]) + (0 * orig[i - 0 + (j + 1) * 8192]) + (0 * orig[i + 1 + (j + 1) * 8192])) / 81;
      sol[i + j * 8192] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
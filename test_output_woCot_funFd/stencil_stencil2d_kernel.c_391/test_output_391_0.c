#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int s;
=======
  int center = 4;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + 1 + 8) * (k - 4) + (256 + 1 + 8) * j + i;
        s += filter[k] * orig[idx];
      }
      sol[i * 256 + j] = s;
=======
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 1; i < 32; i++) {
      idx = i + (j * 32);
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        int cur = filter[k] * orig[idx + align(k - center, 32)];
        sol[idx] += cur;
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
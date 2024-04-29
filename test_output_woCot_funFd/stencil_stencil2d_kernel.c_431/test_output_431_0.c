#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 32; i++) {
=======
  for (i = 0; i < 256; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 32; j++) {
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (((32 + 2) * (32 + 2)) * i) + (((32 + 2) * j) + k);
        s += ((float )filter[k]) * orig[idx];
      }
      sol[((32 + 2) * i) + j] = s;
=======
    for (j = 0; j < 256; j++) {
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 * (k - 4)) + j;
        s += filter[k] * orig[i * 256 + idx];
      }
      sol[i * 256 + j] = s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
//#pragma endscop
}
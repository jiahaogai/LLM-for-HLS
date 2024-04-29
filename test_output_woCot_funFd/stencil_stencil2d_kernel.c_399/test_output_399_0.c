#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
<<<<<<< HEAD
=======
  int index;
//#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + k - 4 + ((j + k - 4) * 8192)];
      }
      sol[i * 8192 + j] = result;
    }
  }
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      result = ((0 + filter[0]) * orig[i * 8192 + j]) + ((0 + filter[1]) * orig[i * 8192 + j + 8191]) + ((0 + filter[2]) * orig[i * 8192 + j + 2 * 8191]) + ((0 + filter[3]) * orig[i * 8192 + j + 3 * 8191]) + ((0 + filter[4]) * orig[i * 8192 + j + 4 * 8191]) + ((0 + filter[5]) * orig[i * 8192 + j + 5 * 8191]) + ((0 + filter[6]) * orig[i * 8192 + j + 6 * 8191]) + ((0 + filter[7]) * orig[i * 8192 + j + 7 * 8191]) + ((0 + filter[8]) * orig[i * 8192 + j + 8 * 8191]);
      sol[i * 8192 + j] = result;
    }
  }
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}
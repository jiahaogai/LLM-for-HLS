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
  int center = 45;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 128 + 2; i++) {
=======
  for (i = 0; i < 64; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    inner:
<<<<<<< HEAD
    for (j = 0; j < 64 + 2; j++) {
      result = ((0 + filter[0]) * orig[i * (64 + 2) + j]) + ((0 + filter[1]) * orig[i * (64 + 2) + j + 1]) + ((0 + filter[2]) * orig[i * (64 + 2) + j + 2]) + ((1 + filter[3]) * orig[i * (64 + 2) + j + 1 + 1]) + ((2 + filter[4]) * orig[i * (64 + 2) + j + 2 + 1]) + ((1 + filter[5]) * orig[i * (64 + 2) + j + 1 + 2]) + ((2 + filter[6]) * orig[i * (64 + 2) + j + 2 + 2]) + ((1 + filter[7]) * orig[i * (64 + 2) + j + 1 + 1]) + ((0 + filter[8]) * orig[i * (64 + 2) + j + 2 + 1]);
      sol[i * (64 + 2) + j] = result;
=======
    for (j = 0; j < 128; j++) {
      idx = i * 128 + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      filter_inner:
      for (k = 0; k < 9; k++) {
        int cur = filter[k];
        int x = i + ((k / 3) - 1);
        int y = j + ((k % 3) - 1);
        if (x < 0) {
          x = 0;
        }
        if (x > 63) {
          x = 63;
        }
        if (y < 0) {
          y = 0;
        }
        if (y > 127) {
          y = 127;
        }
        sol[idx] += cur * orig[x * 128 + y];
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
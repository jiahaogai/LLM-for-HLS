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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  int center = 45;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 8190; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8186; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (k = -4; k <= 4; k++) {
        if ((8191 > ((i + k) - 1))) {
          result += filter[((k + 4) << 3) + (k + 4)] * orig[((i + k) - 1) * 8186 + j - 1];
        }
      }
      sol[(i - 1) * 8186 + j - 1] = result;
=======
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8176; j++) {
      idx = (i * 8192) + j;
      sol[idx] = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 9; k++) {
        sol[idx] += filter[k] * orig[(idx + (k - 4))];
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
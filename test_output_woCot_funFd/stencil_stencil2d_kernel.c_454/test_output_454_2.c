#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int s;
=======
  int result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8191; j++) {
<<<<<<< HEAD
      s = 0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        idx = (i + (-1 + k)) * 8192 + (j + (-1 + k));
        s += filter[k] * orig[idx];
      }
      sol[i * 8192 + j] = s;
=======
      result = ((0 + filter[0]) * (orig[i - 1 + (j - 1) * 8192])) + ((0 + filter[1]) * (orig[i - 0 + (j - 1) * 8192])) + ((0 + filter[2]) * (orig[i + 1 + (j - 1) * 8192])) + ((0 + filter[3]) * (orig[i - 1 + (j - 0) * 8192])) + ((1 + filter[4]) * (orig[i - 0 + (j - 0) * 8192])) + ((0 + filter[5]) * (orig[i + 1 + (j - 0) * 8192])) + ((0 + filter[6]) * (orig[i - 1 + (j + 1) * 8192])) + ((0 + filter[7]) * (orig[i - 0 + (j + 1) * 8192])) + ((0 + filter[8]) * (orig[i + 1 + (j + 1) * 8192]));
      sol[i + j * 8192] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
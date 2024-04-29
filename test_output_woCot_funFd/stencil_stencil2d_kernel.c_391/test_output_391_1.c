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
  double X;
  double Y;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
<<<<<<< HEAD
#pragma ACCEL TILE FACTOR=auto{8}
=======
#pragma ACCEL TILE FACTOR=auto{1}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
<<<<<<< HEAD
      val = 0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + orig[i + (-4 + k)]) % 256;
        val += filter[k] * orig[j + (-4 + idx)];
      }
      sol[i * 256 + j] = val;
=======
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        X = orig[i * 256 + j] * filter[k];
        Y = orig[i * 256 + j + k] * filter[k];
        sum += X + Y;
      }
      sol[i * 256 + j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
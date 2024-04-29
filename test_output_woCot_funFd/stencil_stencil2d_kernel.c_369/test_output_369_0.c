<<<<<<< HEAD
#pragma ACCEL kernel
=======
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8186; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{16}
      for (k = -4; k <= 4; k++) {
        result += filter[k + 4] * orig[i + k * 8192];
      }
      sol[i * 8192 + j] = result;
    }
  }
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

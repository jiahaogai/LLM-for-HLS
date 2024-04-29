#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int t;
  int x;
  int y;
=======
  int k;
  int result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      inner:
      for (x = -4; x < 5; x++) {
        y = -4 + x;
        t += filter[x] * orig[i + y * 8192];
      }
      sol[i + j * 8192] = t;
=======
    inner:
    for (j = 0; j < 8192; j++) {
      result = 0;
      middle:
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + k - 4 + ((j + k - 4) * 8192)];
      }
      sol[i * 8192 + j] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
<<<<<<< HEAD
#pragma ACCEL kernel stencil

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int fl;
=======
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
<<<<<<< HEAD
  for (r = 1; r < 8190; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 8190; c++) {
      sol[r * 8192 + c] = 0.0;
      fl = 0;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
<<<<<<< HEAD
      for (i = -4; i <= 4; i++) {
        fl = fl + filter[i + 4] * orig[(r + i) * 8192 + c];
      }
      sol[r * 8192 + c] = fl;
=======
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + (-4 + k)][j + (-4 + k)];
      }
      sol[i][j] = result;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
=======
  int t;
  int pad;
  pad = 1;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    middle:
    for (j = 0; j < 9; j++) {
      int tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
      inner:
      for (k = 0; k < 8; k++) {
        tmp += orig[i * 8 + k] * filter[j * 8 + k];
      }
      result = tmp;
      sol[i * 9 + j] = result;
=======
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (k = -4; k < 5; k++) {
        int idx = (i * 8) + j + k;
        t += filter[4 + k] * orig[pad + idx];
      }
      sol[(i * 8) + j] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
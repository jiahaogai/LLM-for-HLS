#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int tmp;
=======
  int t;
  int row;
  int col;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    tmp = 0;
=======
  for (i = 0; i < 256; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
<<<<<<< HEAD
    inner:
    for (j = 0; j < 9; j++) {
      tmp += orig[i + (j - 4)] * filter[j];
    }
    sol[i] = tmp;
=======
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      inner:
      for (k = -4; k < 5; k++) {
        row = ((4 + i) + k);
        if (row < 0) {
          row = 0;
        }
        if (row > 255) {
          row = 255;
        }
        for (col = -4; col < 5; col++) {
          if (col < 0) {
            col = 0;
          }
          if (col > 255) {
            col = 255;
          }
          t += ((filter[k + 4]) * (orig[row * 256 + col]));
        }
      }
      sol[i * 256 + j] = t;
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
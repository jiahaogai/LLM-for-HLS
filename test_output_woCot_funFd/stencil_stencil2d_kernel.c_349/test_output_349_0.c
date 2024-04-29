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
  int t;
  int pt = 4;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
    inner:
    for (j = 0; j < 9; j++) {
      x = i - 4 + ((j + 1) / 5);
      y = i - 4 + ((j + 1) % 5);
      if (x >= 0 && x < 8192 && y >= 0 && y < 8192) {
        t += orig[y * 8192 + x] * filter[j];
=======
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
    inner:
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      if (k < 0 || k > 8191) {
        t += filter[j] * 0;
      }
       else {
        t += filter[j] * orig[k];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
    sol[i] = t;
  }
}
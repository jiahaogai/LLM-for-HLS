#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int row;
  int col;
  int flit;
=======
  int idx;
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
<<<<<<< HEAD
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33; i++) {
      row = (j - 1) * 32 + i - 1;
      flit = 0;
      
#pragma ACCEL PARALLEL reduction=flit FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        col = (k / 3) * 32 + k % 3;
        flit += orig[row * 32 + col] * filter[k];
      }
      sol[row * 32 + i - 1] = flit;
=======
  outer:
  for (i = 1; i < 8191; i++) {
    middle:
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx] + filter[0] * orig[idx - 8192] + filter[1] * orig[idx - 8191] + filter[2] * orig[idx - 8190] + filter[3] * orig[idx - 8189] + filter[4] * orig[idx - 8188] + filter[5] * orig[idx - 8187] + filter[6] * orig[idx - 8186] + filter[7] * orig[idx - 8185] + filter[8] * orig[idx - 8184];
      sol[idx] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
<<<<<<< HEAD
#pragma ACCEL kernel
=======
Code: #pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int val;
=======
  int row;
  int col;
  int flit;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 32 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 32 + 1; j++) {
      idx = i * (32 + 2) + j;
      val = orig[idx] + filter[0] * orig[idx - 1] + filter[1] * orig[idx - (32 + 2)] + filter[2] * orig[idx + 1] + filter[3] * orig[idx + (32 + 2)] + filter[4] * orig[idx - (32 + 2) * 2] + filter[5] * orig[idx + (32 + 2) * 2] + filter[6] * orig[idx - (32 + 2) * 3] + filter[7] * orig[idx + (32 + 2) * 3];
      sol[idx] = val;
=======
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      row = i * 256;
      col = j * 1;
      sol[row + col] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      for (k = 0; k < 9; k++) {
        flit = filter[k] * orig[row + col + neighbor[k]];
        sol[row + col] += flit;
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
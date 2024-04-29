#pragma ACCEL kernel

<<<<<<< HEAD
void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
=======
void stencil(int orig[8192],int sol[8192],int filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int x;
  int y;
=======
  int bound;
  int flatten_bound;
  int range_l;
  int range_r;
  int range;
  int idxm1;
  int idxp1;
  int idxm8;
  int idxp8;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 128 + 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 64 + 8; j++) {
      idx = i * (64 + 8) + j;
      x = 0;
      
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        y = k + j;
        if (y < 0 || 64 + 8 <= y) {
          continue;
        }
        x += filter[k + 4] * orig[idx + y * (64 + 8)];
      }
      sol[idx] = x;
=======
  bound = 8192;
  flatten_bound = 8;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  range_l = 1;
  range_r = 64 + 1 - 1;
  range = range_r - range_l + 1;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  idxm1 = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  idxp1 = 128;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  idxm8 = -8;
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  idxp8 = 8;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 128; j++) {
      idx = i * 128 + j;
      sol[idx] = ((filter[0] * orig[idx]) + (filter[1] * (orig[idx + idxm1])) + (filter[2] * (orig[idx + idxp1])) + (filter[3] * (orig[idx + idxm8])) + (filter[4] * (orig[idx + idxp8]))) / 8;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
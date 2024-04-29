#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int center;
=======
  int center = 45;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 256; i++) {
=======
  for (i = 0; i < 64; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      center = orig[idx];
      sol[idx] = ((filter[0] * center) + (filter[1] * (center + -1)) + (filter[2] * (center + -2)) + (filter[3] * (center + 1)) + (filter[4] * (center + 2)) + (filter[5] * (center + 3)) + (filter[6] * (center + -3)) + (filter[7] * (center + 4)) + (filter[8] * (center + 5))) / 256;
=======
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 64; j++) {
      idx = i * 64 + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int cur = (k + center - 4) * 64;
        sol[idx] += filter[k] * orig[cur + idx];
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
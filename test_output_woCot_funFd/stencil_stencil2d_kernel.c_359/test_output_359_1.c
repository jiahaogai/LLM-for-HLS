#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int tmp;
=======
  int idx;
  int center = 45;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
<<<<<<< HEAD
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8186; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction = tmp FACTOR=auto{1}
      inner:
      for (k = -4; k <= 4; k++) {
        tmp += filter[4 + k] * orig[i + k * 8192];
      }
      sol[i * 8192 + j] = tmp;
=======
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8186; j++) {
      idx = (8192 + center - (i - 1)) % 8192;
      sol[idx] = ((filter[0] * orig[idx]) + (filter[1] * (orig[idx + 1] + orig[idx - 1])) + (filter[2] * (orig[idx + 2] + orig[idx - 2])) + (filter[3] * (orig[idx + 3] + orig[idx - 3])) + (filter[4] * (orig[idx + 4] + orig[idx - 4])) + (filter[5] * (orig[idx + 5] + orig[idx - 5])) + (filter[6] * (orig[idx + 6] + orig[idx - 6])) + (filter[7] * (orig[idx + 7] + orig[idx - 7])) + (filter[8] * orig[idx + 8])) % 255;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
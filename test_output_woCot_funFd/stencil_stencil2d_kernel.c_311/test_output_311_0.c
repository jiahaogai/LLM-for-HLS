#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int t;
  int pt = 4;
=======
  int k;
  int idx;
  int center;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{14}
    inner:
    for (j = 0; j < 9; j++) {
      t += orig[i + j - pt] * filter[j];
    }
    sol[i] = t;
=======
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      center = orig[idx];
      sol[idx] = ((filter[0] * center) + (filter[1] * (center + -8192)) + (filter[2] * (center + -8192 * 2))) + ((filter[3] * center) + (filter[4] * (center + 8192)) + (filter[5] * (center + 8192 * 2))) + ((filter[6] * center) + (filter[7] * (center + -8192 * 8)) + (filter[8] * (center + 8192 * 8)));
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
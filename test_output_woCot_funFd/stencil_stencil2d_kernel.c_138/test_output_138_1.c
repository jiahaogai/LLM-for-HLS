#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int idx;
  int val;
=======
  int tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx] + filter[0] * orig[idx - 8192] + filter[1] * orig[idx - 8192 + 1] + filter[2] * orig[idx - 8192 + 2] + filter[3] * orig[idx - 1] + filter[4] * orig[idx + 1] + filter[5] * orig[idx + 2] + filter[6] * orig[idx + 8192] + filter[7] * orig[idx + 8192 + 1] + filter[8] * orig[idx + 8192 + 2];
      sol[idx] = val;
=======
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for (k = 0; k < 8; k++) {
        tmp += orig[i * 8 + k] * filter[j * 8 + k];
      }
      sol[i * 8 + j] = tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
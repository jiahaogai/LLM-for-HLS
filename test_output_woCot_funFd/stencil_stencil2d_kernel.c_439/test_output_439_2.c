#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int result;
=======
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int v;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 16; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 16; j < 8172; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4; k <= 4; k++) {
        result += filter[4 + k] * orig[i + k * 128];
      }
      sol[i * 128 + j] = result;
=======
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 128; j++) {
      idx0 = i * 128 + j;
      idx = idx0 * 8;
      v = orig[idx0];
      idx1 = (i - 1) * 128 + j;
      idx = idx + 1;
      if (idx1 < 0) {
        idx1 = 0;
      }
      if (idx1 > 8191) {
        idx1 = 8191;
      }
      v += orig[idx1] * filter[0];
      idx2 = i * 128 + (j - 1);
      idx = idx + 1;
      if (idx2 < 0) {
        idx2 = 0;
      }
      if (idx2 > 8191) {
        idx2 = 8191;
      }
      v += orig[idx2] * filter[1];
      idx1 = (i - 1) * 128 + (j - 1);
      idx = idx + 1;
      if (idx1 < 0) {
        idx1 = 0;
      }
      if (idx1 > 8191) {
        idx1 = 8191;
      }
      v += orig[idx1] * filter[2];
      idx = idx + 1;
      v += orig[idx] * filter[3];
      idx1 = (i + 1) * 128 + (j - 1);
      idx = idx + 1;
      if (idx1 < 0) {
        idx1 = 0;
      }
      if (idx1 > 8191) {
        idx1 = 8191;
      }
      v += orig[idx1] * filter[4];
      idx = idx + 1;
      v += orig[idx] * filter[5];
      idx1 = (i + 1) * 128 + j;
      idx = idx + 1;
      if (idx1 < 0) {
        idx1 = 0;
      }
      if (idx1 > 8191) {
        idx1 = 8191;
      }
      v += orig[idx1] * filter[6];
      idx = idx + 1;
      v += orig[idx] * filter[7];
      idx1 = (i + 1) * 128 + (j + 1);
      idx = idx + 1;
      if (idx1 < 0) {
        idx1 = 0;
      }
      if (idx1 > 8191) {
        idx1 = 8191;
      }
      v += orig[idx1] * filter[8];
      sol[idx0] = v;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
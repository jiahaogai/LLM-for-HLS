#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int s;
=======
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
<<<<<<< HEAD
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8186; j++) {
      s = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = -4; k <= 4; k++) {
        idx = (i - 1) * 8186 + j + k;
        if (idx < 0) {
          idx = 0;
        }
        else if (idx > 8183) {
          idx = 8183;
        }
        s += ((double )filter[k + 4]) * orig[idx];
      }
      sol[i * 8186 + j] = s;
=======
  for (i = 1; i < 32 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 32 + 1; j++) {
      idx = i * (32 + 2) + j;
      val = orig[idx] + filter[0] * orig[idx - 1] + filter[1] * orig[idx - (32 + 2)] + filter[2] * orig[idx - (32 + 2)] + filter[3] * orig[idx - 1] + filter[4] * orig[idx + 1] + filter[5] * orig[idx + (32 + 2)] + filter[6] * orig[idx + (32 + 2)] + filter[7] * orig[idx - 1] + filter[8] * orig[idx + 1];
      sol[idx] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
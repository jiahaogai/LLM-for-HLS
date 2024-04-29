#pragma ACCEL kernel stencil

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int oidx;
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        oidx = idx + ((k - 4) * 256);
        val += filter[k] * orig[oidx];
      }
      sol[idx] = val;
    }
=======
  for (i = 1; i < 8191; i++) {
     for (j = 1; j < 8191; j++) {
        idx = i * 8192 + j;
        val = orig[idx] + filter[0] * orig[idx - 8192] + filter[1] * orig[idx - 8192 + 1] + filter[2] * orig[idx - 8192 + 2] + filter[3] * orig[idx - 1] + filter[4] * orig[idx + 1] + filter[5] * orig[idx + 2] + filter[6] * orig[idx + 8192] + filter[7] * orig[idx + 8192 + 1] + filter[8] * orig[idx + 8192 + 2];
        sol[idx] = val;
     }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
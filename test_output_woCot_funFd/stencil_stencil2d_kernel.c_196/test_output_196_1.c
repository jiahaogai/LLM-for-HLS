#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
<<<<<<< HEAD
  int k;
  int idx;
  int center;
=======
  int ti;
  int tj;
  int idx;
  int fid;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 1; i < 8191; i++) {
=======
  for (i = 0; i < 256; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
<<<<<<< HEAD
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      center = orig[idx];
      sol[idx] = ((filter[0] * center) + (filter[1] * (center + -8192)) + (filter[2] * (center + -8192 * 2))) + ((filter[3] * (center + 8192)) + (filter[4] * (center + 8192 * 2)) + (filter[5] * (center + 8192 * 3))) + ((filter[6] * (center + -8192 * 3)) + (filter[7] * (center + -8192 * 4)) + (filter[8] * center));
=======
    for (j = 0; j < 256; j++) {
      ti = i - 4;
      tj = j - 4;
      idx = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      inner:
      for (fid = 0; fid < 9; fid++) {
        if (ti + fid > -1 && tj + fid > -1 && ti + fid < 256 && tj + fid < 256) {
          idx += filter[fid] * orig[ti + fid + 8 * tj];
        }
      }
      sol[i * 256 + j] = idx;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[256])
{
  int i;
  int j;
  int k;
  int k_col;
<<<<<<< HEAD
  int flush;
  int off;
=======
  int buf;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8192; i++) {
    sol[i] = ((int )0);
    
#pragma ACCEL PIPELINE auto{}
=======
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{flatten}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8; j++) {
      off = i - 4 + j;
      if (off < 0) {
        off += 8;
      }
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 8; k++) {
        k_col = off + 4 + k;
        if (k_col >= 8192) {
          k_col -= 8192;
        }
        sol[i] += ((filter[k]) * orig[k_col]);
      }
=======
    for (j = 8; j < 8184; j += 8) {
      buf = ((orig[i - 1] + orig[i + 1]) + (orig[j - 1] + orig[j + 1])) + orig[j];
      sol[j] = buf;
      k_col:
      for (k = 0; k < 256; k++) {
        if ((((buf > filter[k]) ? 1 : 0) ^ 0x1) != 0) {
          break;
          k_col = 0;
        }
      }
      sol[j] = k;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
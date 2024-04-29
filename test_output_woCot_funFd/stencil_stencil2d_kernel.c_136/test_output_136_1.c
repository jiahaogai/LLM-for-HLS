#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int idx0;
  int idx1;
  int idx2;
  int idx3;
  int idx4;
  int idx5;
  int idx6;
  int idx7;
  int idx8;
=======
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
<<<<<<< HEAD
  for (i = 0; i < 8; i++) {
=======
  for (i = 0; i < 256; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8; j++) {
      idx0 = i * 64 + j * 8;
      idx = idx0;
      idx1 = idx0 + 1;
      idx2 = idx0 + 2;
      idx3 = idx0 + 3;
      idx4 = idx0 + 4;
      idx5 = idx0 + 5;
      idx6 = idx0 + 6;
      idx7 = idx0 + 7;
      idx8 = idx0 + 8;
      sol[idx] = ((filter[0] * orig[idx0]) + (filter[1] * orig[idx1]) + (filter[2] * orig[idx2]) + (filter[3] * orig[idx3]) + (filter[4] * orig[idx4]) + (filter[5] * orig[idx5]) + (filter[6] * orig[idx6]) + (filter[7] * orig[idx7]) + (filter[8] * orig[idx8])) >> 16;
      sol[idx1] = ((filter[0] * orig[idx8]) + (filter[1] * orig[idx0]) + (filter[2] * orig[idx1]) + (filter[3] * orig[idx2]) + (filter[4] * orig[idx3]) + (filter[5] * orig[idx4]) + (filter[6] * orig[idx5]) + (filter[7] * orig[idx6]) + (filter[8] * orig[idx7])) >> 16;
      sol[idx2] = ((filter[0] * orig[idx7]) + (filter[1] * orig[idx8]) + (filter[2] * orig[idx0]) + (filter[3] * orig[idx1]) + (filter[4] * orig[idx2]) + (filter[5] * orig[idx3]) + (filter[6] * orig[idx4]) + (filter[7] * orig[idx5]) + (filter[8] * orig[idx6])) >> 16;
      sol[idx3] = ((filter[0] * orig[idx6]) + (filter[1] * orig[idx7]) + (filter[2] * orig[idx8]) + (filter[3] * orig[idx0]) + (filter[4] * orig[idx1]) + (filter[5] * orig[idx2]) + (filter[6] * orig[idx3]) + (filter[7] * orig[idx4]) + (filter[8] * orig[idx5])) >> 16;
      sol[idx4] = ((filter[0] * orig[idx5]) + (filter[1] * orig[idx6]) + (filter[2] * orig[idx7]) + (filter[3] * orig[idx8]) + (filter[4] * orig[idx0]) + (filter[5] * orig[idx1]) + (filter[6] * orig[idx2]) + (filter[7] * orig[idx3]) + (filter[8] * orig[idx4])) >> 16;
      sol[idx5] = ((filter[0] * orig[idx4]) + (filter[1] * orig[idx5]) + (filter[2] * orig[idx6]) + (filter[3] * orig[idx7]) + (filter[4] * orig[idx8]) + (filter[5] * orig[idx0]) + (filter[6] * orig[idx1]) + (filter[7] * orig[idx2]) + (filter[8] * orig[idx3])) >> 16;
      sol[idx6] = ((filter[0] * orig[idx3]) + (filter[1] * orig[idx4]) + (filter[2] * orig[idx5]) + (filter[3] * orig[idx6]) + (filter[4] * orig[idx7]) + (filter[5] * orig[idx8]) + (filter[6] * orig[idx0]) + (filter[7] * orig[idx1]) + (filter[8] * orig[idx2])) >> 16;
      sol[idx7] = ((filter[0] * orig[idx2]) + (filter[1] * orig[idx3]) + (filter[2] * orig[idx4]) + (filter[3] * orig[idx5]) + (filter[4] * orig[idx6]) + (filter[5] * orig[idx7]) + (filter[6] * orig[idx8]) + (filter[7] * orig[idx0]) + (filter[8] * orig[idx1])) >> 16;
      sol[idx8] = ((filter[0] * orig[idx1]) + (filter[1] * orig[idx2]) + (filter[2] * orig[idx3]) + (filter[3] * orig[idx4]) + (filter[4] * orig[idx5]) + (filter[5] * orig[idx6]) + (filter[6] * orig[idx7]) + (filter[7] * orig[idx8]) + (filter[8] * orig[idx0])) >> 16;
=======
    for (j = 0; j < 256; j++) {
      val = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + orig[i + ((k - 4) % 256)]) % 256;
        val += filter[k] * orig[j + ((idx - 4) % 256)];
      }
      sol[i * 256 + j] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
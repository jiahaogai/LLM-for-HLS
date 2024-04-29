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
  int idx0;
  int idx1;
  int idx2;
  int idx3;
  int idx4;
  int idx5;
  int idx6;
  int idx7;
  int idx8;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 256; j++) {
<<<<<<< HEAD
      s = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        idx = (256 + 1 + 8) * (k - 4) + i * (256 + 1 + 8) + j;
        s += ((double )filter[k]) * orig[idx];
      }
      sol[i * 256 + j] = s;
=======
      idx0 = i * 256 + j;
      idx = idx0;
      idx1 = idx0 + 1;
      idx2 = idx1 + 1;
      idx3 = idx0 + 256;
      idx4 = idx1 + 256;
      idx5 = idx2 + 256;
      idx6 = idx3 - 1;
      idx7 = idx4 - 1;
      idx8 = idx5 - 1;
      sol[idx0] = filter[0] * orig[idx0] + filter[1] * (orig[idx1] + orig[idx6]) + filter[2] * (orig[idx2] + orig[idx7]) + filter[3] * (orig[idx3] + orig[idx8]) + filter[4] * orig[idx4] + filter[5] * (orig[idx5] + orig[idx8 - 256]) + filter[6] * (orig[idx8 - 1] + orig[idx0 + 1]);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
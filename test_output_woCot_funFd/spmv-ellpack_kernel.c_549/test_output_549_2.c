#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 0; j < 49; j++) {
<<<<<<< HEAD
    for (i = 0; i < 16; i++) {
      out[cols[j * 16 + i]] += nzval[j * 16 + i] * vec[j];
=======
    for (i = 0; i < 494; i++) {
      if (cols[i] == j) {
        out[i] += nzval[i] * vec[j];
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
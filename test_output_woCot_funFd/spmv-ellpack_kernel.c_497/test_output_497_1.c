#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{8}
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
<<<<<<< HEAD
  for (j = 0; j < 16; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{8}
    for (i = 0; i < 48; i++) {
      out[cols[j * 48 + i]] += nzval[j * 48 + i] * vec[j];
=======
  for (j = 0; j < 64; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{8}
    for (i = 0; i < 64; i++) {
      out[cols[j * 64 + i]] += nzval[j * 64 + i] * vec[j];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
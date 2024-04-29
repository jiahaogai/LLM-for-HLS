#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 494; i++) {
    out[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    for (j = 0; j < 40; j++) {
      out[i] += nzval[i * 40 + j] * vec[cols[i * 40 + j]];
=======
    for (j = 0; j < 32; j++) {
      out[i] += nzval[i * 32 + j] * vec[cols[i * 32 + j]];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
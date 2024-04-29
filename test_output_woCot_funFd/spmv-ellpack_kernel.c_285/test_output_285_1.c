<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
#pragma ACCEL kernel

>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (j = 0; j < 10; j++) {
      out[i] += nzval[cols[i + j * 494] - 1] * vec[cols[i + j * 494] - 1];
=======
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
    out[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 32; j++) {
      out[i] += nzval[i * 32 + j] * vec[cols[i * 32 + j]];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
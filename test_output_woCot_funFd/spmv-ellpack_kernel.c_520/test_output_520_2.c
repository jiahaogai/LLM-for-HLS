#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 494; i++) {
    out[i] = 0.0;
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 4; j++) {
      out[i] += nzval[(i * 4) + j] * vec[cols[(i * 4) + j]];
=======
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 16; j++) {
      out[i] += nzval[(i * 16) + j] * vec[cols[(i * 16) + j]];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[4940],double out[4940])
{
  int i;
  int j;
<<<<<<< HEAD
=======
  for (i = 0; i < 4940; i++) 
    out[i] = ((double )0);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 4940; i++) {
<<<<<<< HEAD
    out[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      out[i] += nzval[i * 4 + j] * vec[cols[i * 4 + j]];
    }
=======
    out[cols[i]] += nzval[i] * vec[i];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
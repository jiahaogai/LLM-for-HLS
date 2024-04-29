#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 0; j < 4940; j++) {
<<<<<<< HEAD
    out[cols[j]] += nzval[j] * vec[j >> 5];
=======
    out[cols[j]] += nzval[j] * vec[j / 80 + 0];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
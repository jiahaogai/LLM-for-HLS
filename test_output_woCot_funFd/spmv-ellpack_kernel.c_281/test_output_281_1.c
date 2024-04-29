#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
<<<<<<< HEAD
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
=======
  double sum;
  double val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (j = 0; j < 4940; j++) {
    out[cols[j]] += nzval[j] * vec[j / 64];
=======
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    for (j = 0; j < 49; j++) {
      val = nzval[i * 49 + j];
      sum += val * vec[cols[i * 49 + j]];
    }
    out[i] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
<<<<<<< HEAD
  for (j = 0; j < 4940; j++) {
    out[cols[j]] += nzval[j] * vec[j];
=======
  for (j = 0; j < 494; j++) {
    double sum = (double )0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
    for (j = 0; j < 32; j++) {
      sum += nzval[cols[j] - 1] * vec[cols[j] - 1];
    }
    out[j] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
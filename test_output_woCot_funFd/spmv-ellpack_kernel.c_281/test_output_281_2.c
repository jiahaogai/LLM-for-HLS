#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
<<<<<<< HEAD
=======
  double val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
<<<<<<< HEAD
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 49; j++) {
      sum += nzval[i * 49 + j] * vec[cols[i * 49 + j]];
=======
    for (j = 0; j < 49; j++) {
      val = nzval[i * 49 + j];
      sum += val * vec[cols[i * 49 + j]];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
    out[i] = sum;
  }
}
#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
<<<<<<< HEAD
=======
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = cols[i]; j < cols[i + 1]; j++) {
      sum += nzval[j] * vec[cols[j]];
    }
    out[i] = sum;
  }
}
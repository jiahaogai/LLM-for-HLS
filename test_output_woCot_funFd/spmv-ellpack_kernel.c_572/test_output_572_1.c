#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
<<<<<<< HEAD
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
=======
  int index;
  int n;
  double sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
<<<<<<< HEAD
  for (j = 0; j < 4940; j++) {
    out[cols[j]] += nzval[j] * vec[j / 64];
=======
  loop:
  for (n = 0; n < 494; n++) {
    sum = ((double )0);
    indx:
    for (index = cols[n]; index < cols[n + 1]; index++) {
      sum += nzval[index] * vec[cols[index]];
    }
    out[n] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
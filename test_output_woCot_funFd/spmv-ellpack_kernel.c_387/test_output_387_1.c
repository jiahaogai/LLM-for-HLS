#pragma ACCEL kernel

<<<<<<< HEAD
void ellpack(double nzval[15],int cols[15],double vec[3],double out[1])
{
  int i;
  int j;
=======
void ellpack(double nzval[25],int cols[25],double vec[4],double out[1])
{
  int i;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  double sum;
  sum = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
  for (i = 0; i < 15; i++) {
    sum += nzval[i] * vec[cols[i]];
=======
  for (i = 0; i < 25; i++) {
    sum += nzval[i] * vec[cols[i] - 1];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
  out[0] = sum;
}
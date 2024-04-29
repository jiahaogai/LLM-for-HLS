#pragma ACCEL kernel

<<<<<<< HEAD
void ellpack(double nzval[120],int cols[120],double vec[24],double out[16])
{
  int i;
  int j;
  double sum;
=======
void ellpack(double nzval[210],int cols[210],double vec[10],double out[10])
{
  int i;
  int j;
  for (i = 0; i < 10; i++) 
    out[i] = ((double )0);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
  for (i = 0; i < 16; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 4; j++) {
      sum += nzval[i * 4 + j] * vec[cols[i * 4 + j]];
    }
    out[i] = sum;
=======
  for (j = 0; j < 210; j++) {
    int idx;
    idx = cols[j];
    out[idx] += nzval[j] * vec[idx];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
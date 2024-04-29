#pragma ACCEL kernel

<<<<<<< HEAD
void ellpack(double nzval[120],int cols[120],double vec[24],double out[16])
{
  int i;
  int j;
//#pragma scop
=======
void ellpack(double nzval[200],int cols[200],double vec[25],double out[100])
{
  int i;
  int j;
  double sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
  for (i = 0; i < 16; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[cols[j]];
    }
  }
//#pragma endscop
=======
  for (i = 0; i < 100; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      sum += nzval[j] * vec[cols[j]];
    }
    out[i] = sum;
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}
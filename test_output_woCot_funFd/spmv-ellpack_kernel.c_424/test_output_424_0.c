#pragma ACCEL kernel

<<<<<<< HEAD
void ellpack(double nzval[210],int cols[210],double vec[10],double out[10])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 10; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      sum += nzval[j] * vec[cols[j]];
    }
    out[i] = sum;
  }
=======
void ellpack(double nzval[16],int cols[8],double vec[4],double out[4])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 4; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[j - cols[i]];
    }
  }
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}
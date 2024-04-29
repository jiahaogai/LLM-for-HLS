#pragma ACCEL kernel

<<<<<<< HEAD
void ellpack(double nzval[16],int cols[16],double vec[4],double out[4])
{
  int i;
  int j;
  double sum;
  sum = ((double )0);
=======
void ellpack(double nzval[110],int cols[110],double vec[10],double out[10])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 10; i++) 
    out[i] = ((double )0);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
<<<<<<< HEAD
  for (i = 0; i < 4; i++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sum += nzval[i * 4 + j] * vec[cols[i * 4 + j]];
    }
    out[i] = sum;
  }
=======
  for (j = 0; j < 110; j++) {
    int idx;
    idx = cols[j];
    out[idx] += nzval[j] * vec[j];
  }
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}
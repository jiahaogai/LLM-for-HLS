#pragma ACCEL kernel

<<<<<<< HEAD
void ellpack(double nzval[16],int cols[16],double vec[4],double out[4])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 4; i++) 
    out[i] = ((double )0);
=======
void ellpack(double nzval[32],int cols[32],double vec[2],double out[1])
{
  int i;
  int j;
  double sum;
  sum = ((double )0);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
<<<<<<< HEAD
  for (j = 0; j < 4; j++) {
    for (i = 0; i < 16; i++) {
      out[j] += nzval[i] * vec[cols[i] - 1];
    }
  }
//#pragma endscop
=======
  for (i = 0; i < 4; i++) {
    sum += nzval[i] * vec[cols[i]];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  out[0] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}
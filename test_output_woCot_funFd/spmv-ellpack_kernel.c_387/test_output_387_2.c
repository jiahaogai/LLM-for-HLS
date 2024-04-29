#pragma ACCEL kernel

<<<<<<< HEAD
void ellpack(double nzval[192],int cols[192],double vec[24],double out[12])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 12; i++) 
    out[i] = ((double )0);
=======
void ellpack(double nzval[16],int cols[16],double vec[4],double out[1])
{
  int i;
  int j;
  double sum;
  sum = ((double )0);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
  for (j = 0; j < 192; j++) {
    out[cols[j]] += nzval[j] * vec[j / 8];
  }
//#pragma endscop
=======
  for (i = 0; i < 4; i++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 16; j++) {
      sum += nzval[j] * vec[cols[j]];
    }
    out[i] = sum;
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}
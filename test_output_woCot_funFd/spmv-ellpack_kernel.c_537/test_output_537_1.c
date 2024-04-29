#pragma ACCEL kernel

<<<<<<< HEAD
void ellpack(double nzval[4096],int cols[4096],double vec[64],double out[64])
{
  int i;
  int j;
=======
void ellpack(double nzval[192],int cols[192],double vec[16],double out[16])
{
  int i;
  int j;
//#pragma scop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
<<<<<<< HEAD
  spmv_1:
  for (i = 0; i < 64; i++) {
    out[i] = ((double )0);
    spmv_2:
    for (j = 0; j < 64; j++) {
      out[i] += nzval[cols[j] + i * 64] * vec[j];
    }
  }
=======
  for (i = 0; i < 16; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      out[i] += nzval[cols[i + j * 16] - 1] * vec[j];
    }
  }
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}
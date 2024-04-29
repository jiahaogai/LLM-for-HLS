#pragma ACCEL kernel

<<<<<<< HEAD
void ellpack(double nzval[2304],int cols[1008],double vec[16],double out[16])
{
  int i;
  int j;
  double sum;
  double ELEM_FACTOR = 1.0;
=======
void ellpack(double nzval[128],int cols[128],double vec[16],double out[16])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 16; i++) 
    out[i] = ((double )0);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
<<<<<<< HEAD
  spmv_1:
  for (i = 0; i < 16; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 4; j++) {
      sum += nzval[cols[i + (j << 4)]] * vec[j];
    }
    out[i] = sum * ELEM_FACTOR;
  }
=======
  for (j = 0; j < 128; j++) {
    int idx;
    idx = cols[j];
    out[idx] += nzval[j] * vec[j];
  }
//#pragma endscop
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}
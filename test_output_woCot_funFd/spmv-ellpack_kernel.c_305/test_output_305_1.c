<<<<<<< HEAD
#pragma ACCEL kernel
=======
Code: 
 #pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  spmv_1:
  for (i = 0; i < 49; i++) {
    out[i] = ((double )0);
    spmv_2:
    for (j = 0; j < 16; j++) {
      out[i] += nzval[i * 16 + j] * vec[cols[i * 16 + j]];
=======
  for (i = 0; i < 49; i++) {
    out[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 5; j++) {
      out[i] += nzval[i * 5 + j] * vec[cols[i * 5 + j]];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
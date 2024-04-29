#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 49; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
    for (j = 0; j < 4; j++) {
      out[i] += nzval[i * 4 + j] * vec[cols[i * 4 + j]];
=======
    for (j = 0; j < 494; j++) {
      out[i] += nzval[j] * vec[cols[j] - 1];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
//#pragma endscop
}
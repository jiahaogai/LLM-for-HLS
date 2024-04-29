<<<<<<< HEAD
The resulting C code is:

c
=======
Code: 
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
 #pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double Si;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
<<<<<<< HEAD
  for (i = 0; i < 494; i++) {
    double sum = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
=======
  ellpack_1:
  for (i = 0; i < 494; i++) {
    double sum = ((double )0);
    ellpack_2:
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 0; j < 10; j++) {
      Si = nzval[j + i * 10] * vec[cols[j + i * 10]];
      sum += Si;
    }
    out[i] = sum;
  }
}
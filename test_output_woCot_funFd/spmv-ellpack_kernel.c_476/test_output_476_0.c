<<<<<<< HEAD
#pragma ACCEL kernel
=======
The error(s) occurred in the following function(s):
ellpack
double nzval[4940]
int cols[4940]
double vec[494]
double out[494]
//#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
<<<<<<< HEAD
  for (j = 0; j < 9; j++) {
=======
  for (j = 0; j < 493; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    i = cols[j];
    out[i] += nzval[j] * vec[j];
  }
}
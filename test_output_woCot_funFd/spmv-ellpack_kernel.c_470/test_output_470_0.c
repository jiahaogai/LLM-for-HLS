#pragma ACCEL kernel

<<<<<<< HEAD
void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int i;
  int j;
  for (i = 0; i < 49; i++) 
=======
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
<<<<<<< HEAD
  for (j = 0; j < 494; j++) {
    out[cols[j]] += nzval[j] * vec[j / 8];
=======
  for (j = 0; j < 49; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{1}
    for (i = 0; i < 494; i++) {
      out[cols[i]] += nzval[i] * vec[j];
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
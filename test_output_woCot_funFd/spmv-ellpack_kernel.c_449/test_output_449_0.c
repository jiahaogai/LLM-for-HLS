#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
<<<<<<< HEAD
=======
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
<<<<<<< HEAD
  for (i = 0; i < 494; i++) {
    out[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{1}
    for (j = 0; j < 10; j++) {
      out[i] += nzval[i * 10 + j] * vec[cols[i * 10 + j]];
    }
=======
  for (j = 0; j < 10; j++) {
    int idx = cols[j];
    out[idx] += nzval[j] * vec[i];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
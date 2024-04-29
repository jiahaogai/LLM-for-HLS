#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
<<<<<<< HEAD
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
<<<<<<< HEAD
    double sum = ((double )0);
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
    for (j = 0; j < 20; j++) {
      int nzidx = i * 20 + j;
      sum += nzval[nzidx] * vec[cols[nzidx]];
    }
    out[i] = sum;
=======
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 5; j++) {
      out[i] += nzval[(i * 5 + j)] * vec[cols[(i * 5 + j)]];
    }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}
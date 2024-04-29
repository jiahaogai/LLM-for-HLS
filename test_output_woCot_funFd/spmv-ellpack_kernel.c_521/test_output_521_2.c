#pragma ACCEL PIPELINE auto{flatten}
<<<<<<< HEAD
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}

#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}

#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}

#pragma ACCEL kernel

=======

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{8}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (j = 0; j < 64; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{8}
    for (i = 0; i < 64; i++) {
      out[cols[j * 64 + i]] += nzval[j * 64 + i] * vec[j];
=======
  for (j = 0; j < 40; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{1}
    for (i = 0; i < 494; i++) {
      out[i] += nzval[cols[i] + j * 494] * vec[j];
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
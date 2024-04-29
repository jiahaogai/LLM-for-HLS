<<<<<<< HEAD
#pragma ACCEL kernel
=======
Code: 
 #pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (i = 0; i < 494; i++) {
    out[i] = 0.0;
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{16}
=======
#pragma ACCEL PARALLEL FACTOR=auto{19}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    for (j = 0; j < 32; j++) {
      out[i] += nzval[i * 32 + j] * vec[cols[i * 32 + j]];
    }
  }
}
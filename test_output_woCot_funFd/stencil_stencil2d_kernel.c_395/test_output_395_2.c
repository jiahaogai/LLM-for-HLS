#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
<<<<<<< HEAD
  int s;
=======
  int val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
<<<<<<< HEAD
  for (i = 1; i < 32 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 32 + 1; j++) {
      s = 0.0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{32}
      for (k = 0; k < 9; k++) {
        idx = (32 + 2) * (k - 4) + i - 1;
        s += filter[k] * orig[idx * (32 + 2) + j - 1];
      }
      sol[i * (32 + 2) + j - 1] = s;
=======
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      val = ((filter[0] * orig[idx]) + (filter[1] * (orig[idx + 1])) + (filter[2] * (orig[idx + 2]))) + ((filter[3] * (orig[idx + 256])) + (filter[4] * (orig[idx + 257])) + (filter[5] * (orig[idx + 258])));
      val += ((filter[6] * (orig[idx + 512])) + (filter[7] * (orig[idx + 513])) + (filter[8] * (orig[idx + 514])));
      sol[idx] = val;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
}
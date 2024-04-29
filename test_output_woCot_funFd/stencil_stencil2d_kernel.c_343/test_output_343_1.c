<<<<<<< HEAD
#pragma ACCEL kernel
=======
Code: #pragma ACCEL kernel

int main()
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 8; j++) {
      sol[i * 8 + j] = ((filter[0] * orig[i * 8 + j]) + (filter[1] * orig[i * 8 + j + 1]) + (filter[2] * orig[i * 8 + j + 2]) + (filter[3] * orig[i * 8 + j + 3]) + (filter[4] * orig[i * 8 + j + 4]) + (filter[5] * orig[i * 8 + j + 5]) + (filter[6] * orig[i * 8 + j + 6]) + (filter[7] * orig[i * 8 + j + 7]) + (filter[8] * orig[i * 8 + j + 8])) / 256;
    }
  }
//#pragma endscop
}
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

<<<<<<< HEAD
Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8190; j++) {
      sol[i * 8192 + j] = filter[4] * orig[i * 8192 + j] + filter[1] * (orig[i * 8192 + j - 1] + orig[i * 8192 + j + 1]) + filter[2] * (orig[i * 8192 + j - 8192] + orig[i * 8192 + j + 8192]) + filter[3] * (orig[i * 8192 + j - 8] + orig[i * 8192 + j + 8]);
    }
  }
//#pragma endscop
=======
#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    orig[i] = i;
  }
  
#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sol[i] = ((filter[0] * orig[i]) + (filter[1] * orig[i + 1]) + (filter[2] * orig[i + 2]) + (filter[3] * orig[i + 8]) + (filter[4] * orig[i + 9]) + (filter[5] * orig[i + 10]) + (filter[6] * orig[i + 11]) + (filter[7] * orig[i + 12]) + (filter[8] * orig[i + 16])) >> 4;
  }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}
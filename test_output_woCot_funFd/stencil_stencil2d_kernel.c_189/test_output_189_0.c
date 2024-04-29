#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 25 - 1; i++) {
    
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((filter[0] * orig[i - 1][j - 1]) + (filter[1] * orig[i - 1][j]) + (filter[2] * orig[i - 1][j + 1]) + (filter[3] * orig[i][j - 1]) + (filter[4] * orig[i][j]) + (filter[5] * orig[i][j + 1]) + (filter[6] * orig[i + 1][j - 1]) + (filter[7] * orig[i + 1][j]) + (filter[8] * orig[i + 1][j + 1])) / 25;
=======
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((orig[i - 1][j - 1] + orig[i - 1][j] + orig[i - 1][j + 1] + orig[i][j - 1] + orig[i][j] + orig[i][j + 1] + orig[i + 1][j - 1] + orig[i + 1][j] + orig[i + 1][j + 1]) + filter[0]) / ((25 - 1) * (25 - 1));
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    }
  }
//#pragma endscop
}
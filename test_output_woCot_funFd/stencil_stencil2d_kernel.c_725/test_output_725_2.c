After HLS completes its transformations, the resulting hardware is able to process the `orig` array in 16 cycles.
 #pragma ACCEL kernel

void stencil(int orig[40][40],int sol[40][40],int filter[3][3])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 39; j++) {
      sol[i][j] = ((filter[0][0] * orig[i][j]) + (filter[0][1] * orig[i][j + 1]) + (filter[0][2] * orig[i][j + 2])) + ((filter[1][0] * orig[i + 1][j]) + (filter[1][1] * orig[i + 1][j + 1]) + (filter[1][2] * orig[i + 1][j + 2])) + ((filter[2][0] * orig[i + 2][j]) + (filter[2][1] * orig[i + 2][j + 1]) + (filter[2][2] * orig[i + 2][j + 2]));
    }
  }
//#pragma endscop
}
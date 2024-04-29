#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  int x;
  int y;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sol[i][j] = ((filter[0][0] * orig[i][j]) + (filter[0][1] * orig[i][(j + 1) % 4]) + (filter[0][2] * orig[i][(j + 2) % 4])) + ((filter[1][0] * orig[i][(j + 1) % 4]) + (filter[1][1] * orig[i][(j + 2) % 4]) + (filter[1][2] * orig[i][(j + 3) % 4])) + ((filter[2][0] * orig[i][(j + 2) % 4]) + (filter[2][1] * orig[i][(j + 3) % 4]) + (filter[2][2] * orig[i][(j + 4) % 4]));
    }
  }
//#pragma endscop
}
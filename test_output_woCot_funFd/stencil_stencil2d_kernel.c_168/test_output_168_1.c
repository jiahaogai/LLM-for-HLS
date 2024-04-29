#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[126][126])
{
  int i;
  int j;
  int k;
  int r;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 400 - 1; j++) {
      sol[i][j] = 0.0;
      for (k = 0; k < 126; k++) {
        r = i - 63 + k;
        for (s = 0; s < 126; s++) {
          s = j - 63 + s;
          sol[i][j] += filter[k][s] * orig[r][s];
        }
      }
    }
  }
//#pragma endscop
}
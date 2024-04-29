#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[3][3])
{
  int i;
  int j;
  int flatten_filter[9] = {((filter)[0][0]),((filter)[0][1]),((filter)[0][2]),((filter)[1][0]),((filter)[1][1]),((filter)[1][2]),((filter)[2][0]),((filter)[2][1]),((filter)[2][2])};
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 400 - 1; j++) {
      sol[i][j] = ((flatten_filter[0]) * orig[i][j - 1]) + ((flatten_filter[1]) * orig[i][j]) + ((flatten_filter[2]) * orig[i][j + 1]) + ((flatten_filter[3]) * orig[i - 1][j]) + ((flatten_filter[4]) * orig[i][j]) + ((flatten_filter[5]) * orig[i + 1][j]) + ((flatten_filter[6]) * orig[i - 1][j - 1]) + ((flatten_filter[7]) * orig[i - 1][j + 1]) + ((flatten_filter[8]) * orig[i + 1][j - 1]) + ((flatten_filter[9]) * orig[i + 1][j + 1]);
    }
  }
}
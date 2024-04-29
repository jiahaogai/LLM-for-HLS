#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25][25])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    inner:
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((int )filter[0][0] * orig[i - 1][j - 1]) + ((int )filter[0][1] * orig[i - 1][j]) + ((int )filter[0][2] * orig[i - 1][j + 1]) + ((int )filter[1][0] * orig[i][j - 1]) + ((int )filter[1][1] * orig[i][j]) + ((int )filter[1][2] * orig[i][j + 1]) + ((int )filter[2][0] * orig[i + 1][j - 1]) + ((int )filter[2][1] * orig[i + 1][j]) + ((int )filter[2][2] * orig[i + 1][j + 1]);
    }
  }
}
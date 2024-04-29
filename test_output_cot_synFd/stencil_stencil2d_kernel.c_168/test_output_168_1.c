#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int x;
  int y;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      x = ((i - 1 < 0) ? 0 : i - 1);
      y = ((j - 1 < 0) ? 0 : j - 1);
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (y = (y - 1 < 0 ? 0 : y - 1); y < 2; y++) {
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
        for (x = (x - 1 < 0 ? 0 : x - 1); x < 2; x++) {
          sol[i][j] += filter[y][x] * orig[i + x][j + y];
        }
      }
    }
  }
//#pragma endscop
}
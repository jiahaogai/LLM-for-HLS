#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int flatten_filter[81];
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 400 - 1; j++) {
      flatten_filter[(0 * 9) + 4] = filter[0];
      flatten_filter[(1 * 9) + 4] = filter[1];
      flatten_filter[(2 * 9) + 4] = filter[2];
      flatten_filter[(0 * 9) + 3] = filter[3];
      flatten_filter[(1 * 9) + 3] = filter[4];
      flatten_filter[(2 * 9) + 3] = filter[5];
      flatten_filter[(0 * 9) + 2] = filter[6];
      flatten_filter[(1 * 9) + 2] = filter[7];
      flatten_filter[(2 * 9) + 2] = filter[8];
      flatten_filter[(0 * 9) + 1] = 0;
      flatten_filter[(1 * 9) + 1] = 0;
      flatten_filter[(2 * 9) + 1] = 0;
      flatten_filter[(0 * 9) + 0] = 0;
      flatten_filter[(1 * 9) + 0] = 0;
      flatten_filter[(2 * 9) + 0] = 0;
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (x = 0; x < 9; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{16}
        for (y = 0; y < 9; y++) {
          sol[i][j] += flatten_filter[y * 9 + x] * orig[i + (-1 + y)][j + (-1 + x)];
        }
      }
    }
  }
}
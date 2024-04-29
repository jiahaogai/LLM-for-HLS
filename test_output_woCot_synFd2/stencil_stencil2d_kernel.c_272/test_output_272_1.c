#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int tile;
  int ti;
  int tj;
  int fl;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 400 - 1; j++) {
      idx = i - 1;
      idy = j - 1;
      tile = 0;
      inner:
      for (k = 0; k < 9; k++) {
        ti = idx + filter[k];
        tj = idy + filter[k + 1];
        if (ti >= 0 && ti < 400 && tj >= 0 && tj < 400) {
          tile += orig[ti][tj] * filter[k + 2];
        }
      }
      sol[i][j] = tile;
    }
  }
}
#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int ii;
  int jj;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    inner:
    for (j = 0; j < 4; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{32}
      filter:
      for (ii = -1; ii < 2; ii++) {
        int_boundary:
        for (jj = -1; jj < 2; jj++) {
          if (((i + ii) < 0) || ((i + ii) > 3)) {
            {}
          }
          else {
            if (((j + jj) < 0) || ((j + jj) > 3)) {
              {}
            }
            else {
              tmp += orig[i + ii][j + jj] * filter[ii + 1][jj + 1];
            }
          }
        }
      }
      sol[i][j] = tmp;
    }
  }
}
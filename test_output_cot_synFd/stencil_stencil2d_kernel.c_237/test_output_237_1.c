#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int fl;
  int ol;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 4; j++) {
      ol = orig[i][j];
      fl = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      filter_inner:
      for (int r = 0; r < 2; r++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        filter_outer:
        for (int c = 0; c < 2; c++) {
          fl += filter[r][c] * orig[i + ((r - 1))][j + ((c - 1))];
        }
      }
      sol[i][j] = fl;
    }
  }
}
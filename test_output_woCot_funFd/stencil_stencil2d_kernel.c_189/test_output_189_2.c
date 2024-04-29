#pragma ACCEL kernel

void stencil(int orig[25],int sol[25],int filter[25])
{
  int i;
  int j;
  int jj;
  int i_col;
  int col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{126}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 25; j++) {
      i_col = i - 1;
      col = 0;
      
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{2}
      inner:
      while (col < 25) {
        if (i_col < 0) {
          i_col += 25;
        }
        sol[i] += orig[i_col * 25 + col] * filter[col];
        col++;
      }
    }
  }
}
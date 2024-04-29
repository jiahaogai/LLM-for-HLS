#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int row;
  int col;
  int flatten_filter[81];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (c = 1; c < 8191; c++) {
      i = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = -4; j <= 4; j++) {
        if ((((r + j) >= 1) && ((r + j) <= 8192)) && (((c - 4) + j) >= 1)) {
          flatten_filter[i] = filter[j + 4];
          i++;
        }
      }
      col = c - 4;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 0; j < 81; j++) {
        row = r - 4 + (j % 9);
        if ((row >= 1) && (row <= 8192)) {
          sol[col * 8192 + row] = flatten_filter[j];
        }
      }
    }
  }
}
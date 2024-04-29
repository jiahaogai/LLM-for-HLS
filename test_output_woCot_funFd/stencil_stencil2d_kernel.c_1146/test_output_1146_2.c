#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (row = i * 64; row < (i + 1) * 64; row++) {
        for (col = j * 64; col < (j + 1) * 64; col++) {
          flatten_row = row * 8;
          flatten_col = col * 8;
          tmp:
          for (int k = 0; k < 8; k++) {
            t += ((orig[flatten_row + k]) * (filter[k])) ;
          }
        }
      }
      sol[i * 64 + j] = t;
    }
  }
}
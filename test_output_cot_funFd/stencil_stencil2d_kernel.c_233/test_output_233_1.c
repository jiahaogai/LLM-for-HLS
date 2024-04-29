Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flr;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 8192; j++) {
      flr = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = -45; k < -42; k++) {
        row = i + k;
        if (row < 0) {
          row = 0;
        }
        else {
          if (row > 8191) {
            row = 8191;
          }
        }
        col = j - 45;
        if (col < 0) {
          col = 0;
        }
        else {
          if (col > 8191) {
            col = 8191;
          }
        }
        flr += ((orig[row * 8192 + col]) * filter[k + 45]);
      }
      sol[i * 8192 + j] = flr;
    }
  }
}
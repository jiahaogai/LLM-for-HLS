#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 64; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = -4; k <= 4; k++) {
        row = i + k;
        col = j - 4;
        if (row < 0 || row > 8191) {
          row = 0;
        }
        if (col < 0) {
          col = 0;
        }
        t += orig[row * 64 + col] * filter[k + 4];
      }
      sol[i * 64 + j] = t;
    }
  }
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int r;
  int c;
  int temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (r = 1; r < 8190; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 8190; c++) {
      temp = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (i = -4; i <= 4; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        for (j = -4; j <= 4; j++) {
          temp += filter[((i + 4) * 9) + (j + 4)] * orig[r + i][c + j];
        }
      }
      sol[r][c] = temp;
    }
  }
}
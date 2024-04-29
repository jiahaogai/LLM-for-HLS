#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      x = i - 1;
      y = j - 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      while (x < i + 2) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        while (y < j + 2) {
          t += orig[x * 8192 + y] * filter[4 - (((x - i) + 1) + ((y - j) + 1)));
          y++;
        }
        y = j - 1;
        x++;
      }
      sol[i * 8192 + j] = t;
    }
  }
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int r;
  int c;
  int r_up;
  int r_down;
  int c_left;
  int c_right;
  int t;
  int sum;
  r_up = 1;
  r_down = 1;
  c_left = 1;
  c_right = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  loop:
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    row:
    for (c = 1; c < 8191; c++) {
      t = ((r - r_up) * 8191) + (c - c_left);
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      depth:
      for (i = 0; i < 9; i++) {
        j = ((t + i) * 8) + 1;
        sum += orig[j] * filter[i];
      }
      sol[t] = sum;
    }
  }
}
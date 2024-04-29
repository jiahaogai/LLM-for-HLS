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
  int t_up;
  int t_down;
  int t_left;
  int t_right;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_c:
    for (c = 1; c < 8191; c++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{32}
      loop_r_up:
      for (r_up = -1; r_up <= 1; r_up++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{32}
        loop_c_left:
        for (c_left = -1; c_left <= 1; c_left++) {
          t_up = r + r_up;
          t_left = c + c_left;
          if (t_up < 0 || t_up > 8191) {
            t_up = 0;
          }
          if (t_left < 0 || t_left > 8191) {
            t_left = 0;
          }
          t_down = r + 1;
          t_right = c + 1;
          if (t_down < 0 || t_down > 8191) {
            t_down = 0;
          }
          if (t_right < 0 || t_right > 8191) {
            t_right = 0;
          }
          t += filter[r_up + 1] * orig[t_up * 8192 + t_left] + filter[c_left + 1] * orig[t_down * 8192 + t_right];
        }
      }
      sol[r * 8192 + c] = t;
    }
  }
}
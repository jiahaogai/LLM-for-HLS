#pragma ACCEL kernel

void stencil(int orig[25][20][3],int sol[25][20][3],int filter[3][3][3])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  int v;
  int r_s;
  int r_t;
  int r_u;
  int min_r_s;
  int max_r_s;
  int min_r_t;
  int max_r_t;
  int min_r_u;
  int max_r_u;
  int q_s;
  int q_t;
  int q_u;
  int min_q_s;
  int max_q_s;
  int min_q_t;
  int max_q_t;
  int min_q_u;
  int max_q_u;
  int p_s;
  int p_t;
  int p_u;
  int min_p_s;
  int max_p_s;
  int min_p_t;
  int max_p_t;
  int min_p_u;
  int max_p_u;
  int s_q;
  int s_p;
  int s_min;
  int s_max;
  int t_q;
  int t_p;
  int t_min;
  int t_max;
  int u_q;
  int u_p;
  int u_min;
  int u_max;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 3; p++) {
        r_s = r - 1;
        r_t = r + 1;
        r_u = r;
        min_r_s = (0 > r_s?0:r_s);
        max_r_s = (25 > r_s?r_s:25) - 1;
        min_r_t = (0 > r_t?0:r_t);
        max_r_t = (25 > r_t?r_t:25) - 1;
        min_r_u = (0 > r_u?0:r_u);
        max_r_u = (25 > r_u?r_u:25) - 1;
        q_s = q - 1;
        q_t = q + 1;
        q_u = q;
        min_q_s = (0 > q_s?0:q_s);
        max_q_s = (20 > q_s?q_s:20) - 1;
        min_q_t = (0 > q_t?0:q_t);
        max_q_t = (20 > q_t?q_t:20) - 1;
        min_q_u = (0 > q_u?0:q_u);
        max_q_u = (20 > q_u?q_u:20) - 1;
        p_s = p - 1;
        p_t = p + 1;
        p_u = p;
        min_p_s = (0 > p_s?0:p_s);
        max_p_s = (3 > p_s?p_s:3) - 1;
        min_p_t = (0 > p_t?0:p_t);
        max_p_t = (3 > p_t?p_t:3) - 1;
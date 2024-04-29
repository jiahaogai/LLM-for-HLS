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
  int s_min;
  int s_max;
  int t_min;
  int t_max;
  int u_min;
  int u_max;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{2}
      for (p = 0; p < 3; p++) {
        r_s = r - 1;
        r_t = r + 1;
        if (r_s < 0) {
          r_s = 0;
        }
        if (r_t > 24) {
          r_t = 24;
        }
        r_u = r;
        min_r_s = 0;
        max_r_s = 1;
        if (r_s == r_u) {
          min_r_s = 1;
          max_r_s = 2;
        }
        min_r_t = 1;
        max_r_t = 2;
        if (r_t == r_u) {
          min_r_t = 2;
          max_r_t = 3;
        }
        min_r_u = 2;
        max_r_u = 3;
        q_s = q - 1;
        q_t = q + 1;
        if (q_s < 0) {
          q_s = 0;
        }
        if (q_t > 19) {
          q_t = 19;
        }
        q_u = q;
        min_q_s = 0;
        max_q_s = 1;
        if (q_s == q_u) {
          min_q_s = 1;
          max_q_s = 2;
        }
        min_q_t = 1;
        max_q_t = 2;
        if (q_t == q_u) {
          min_q_t = 2;
          max_q_t = 3;
        }
        min_q_u = 2;
        max_q_u = 3;
        p_s = p - 1;
        p_t = p + 1;
        if (p_s < 0) {
          p_s = 0;
        }
        if (p_t > 2) {
          p_t = 2;
        }
        p_u = p;
        min_p_s = 0;
        max_p_s = 1;
        if (p_s == p_u) {
          min_p_s = 1;
          max_p_s = 2;
        }
        min_p_t = 1;
        max_p_t = 2;
        if (p_t == p_u) {
          min_p_t = 2;
          max_p_t = 3;
        }
        min_p_u = 2;
        max_p_u = 3;
        s_min = 0;
        s_max = 2;
        t_min = 0;
        t_max = 2;
        u_min = 0;
        u_max = 2;
        if (1 == 0) {
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          for (s = s_min; s <= s_max; s++) {
            
#pragma ACCEL PIPELINE auto{off}
            
#pragma ACCEL TILE FACTOR=auto{1}
            for (t = t_min; t <= t_max; t++) {
              
#pragma ACCEL PIPELINE auto{off}
              
#pragma ACCEL TILE FACTOR=auto{1}
              for (u = u_min; u <= u_max; u++) {
                sol[r][q][p] += filter[s][t][u] * orig[r_s + s][q_s + t][p_u + u];
              }
            }
          }
        }
        if (1 == 1) {
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          for (s = s_min; s <= s_max; s++) {
            
#pragma ACCEL PIPELINE auto{off}
            
#pragma ACCEL TILE FACTOR=auto{2}
            for (t = t_min; t <= t_max; t++) {
              
#pragma ACCEL PIPELINE auto{off}
              
#pragma ACCEL TILE FACTOR=auto{1}
              for (u = u_min; u <= u_max; u++) {
                sol[r][q][p] += filter[s][t][u] * orig[r_s + s][q_t + t][p_u + u];
              }
            }
          }
        }
        if (1 == 2) {
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          for (s = s_min; s <= s_max; s++) {
            
#pragma ACCEL PIPELINE auto{off}
            
#pragma ACCEL TILE FACTOR=auto{2}
            for (t = t_min; t <= t_max; t++) {
              
#pragma ACCEL PIPELINE auto{flatten}
              
#pragma ACCEL TILE FACTOR=auto{1}
              for (u = u_min; u <= u_max; u++) {
                sol[r][q][p] += filter[s][t][u] * orig[r_s + s][q_u + u][p_u + u];
              }
            }
          }
        }
        if (1 == 3) {
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          for (s = s_min; s <= s_max; s++) {
            
#pragma ACCEL PIPELINE auto{flatten}
            
#pragma ACCEL TILE FACTOR=auto{1}
            for (t = t_min; t <= t_max; t++) {
              
#pragma ACCEL PIPELINE auto{off}
              
#pragma ACCEL TILE FACTOR=auto{1}
              for (u = u_min; u <= u_max; u++) {
                sol[r][q][p] += filter[s][t][u] * orig[r_t + s][q_s + t][p_u + u];
              }
            }
          }
        }
        if (1 == 4) {
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          for (s = s_min; s <= s_max; s++) {
            
#pragma ACCEL PIPELINE auto{flatten}
            
#pragma ACCEL TILE FACTOR=auto{2}
            for (t = t_min; t <= t_max; t++) {
              
#pragma ACCEL PIPELINE auto{off}
              
#pragma ACCEL TILE FACTOR=auto{1}
              for (u = u_min; u <= u_max; u++) {
                sol[r][q][p] += filter[s][t][u] * orig[r_t + s][q_t + t][p_u + u];
              }
            }
          }
        }
        if (1 == 5) {
          
#pragma ACCEL PIPELINE auto{off}
          
#pragma ACCEL TILE FACTOR=auto{1}
          for (s = s_min; s <= s_max; s++) {
            
#pragma ACCEL PIPELINE auto{flatten}
            
#pragma ACCEL TILE FACTOR=auto{1}
            for (t = t_min; t <= t_max; t++) {
              
#pragma ACCEL PIPELINE auto{flatten}
              
#pragma ACCEL TILE FACTOR=auto{1}
              for (u = u_min; u <= u_max; u++) {
                sol[r][q][p] += filter[s][t][u] * orig[r_u + s][q_u + t][p_u + u];
              }
            }
          }
        }
      }
    }
  }
}
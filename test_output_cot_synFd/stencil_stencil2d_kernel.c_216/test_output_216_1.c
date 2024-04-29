#pragma ACCEL kernel

void stencil(int orig[25][20][3],int sol[25][20][3],int filter[9][9][3])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  int v;
  int f;
  int r0 = 1;
  int q0 = 1;
  int p0 = 1;
  int r1 = 24;
  int q1 = 20;
  int p1 = 3;
  int s1;
  int t1;
  int u1;
  int v1;
  int r2 = 1;
  int q2 = 20;
  int p2 = 1;
  int s2 = 24;
  int t2;
  int u2;
  int v2;
  int r3 = 24;
  int q3 = 1;
  int p3 = 1;
  int s3 = 20;
  int t3;
  int u3;
  int v3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  loop_r:
  for (r = r0; r <= r1; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_q:
    for (q = q0; q <= q1; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_p:
      for (p = p0; p <= p1; p++) {
        s1 = (r - 1) < 0 ? 0 : (r - 1);
        t1 = (q - 1) < 0 ? 0 : (q - 1);
        u1 = (p - 1) < 0 ? 0 : (p - 1);
        v1 = (r + 1) > 24 ? 24 : (r + 1);
        t2 = (q + 1) > 20 ? 20 : (q + 1);
        u2 = (p + 1) > 3 ? 3 : (p + 1);
        s2 = (r - 1) < 0 ? 0 : (r - 1);
        v2 = (r + 1) > 24 ? 24 : (r + 1);
        q3 = (q - 1) < 0 ? 0 : (q - 1);
        p3 = (p - 1) < 0 ? 0 : (p - 1);
        s3 = (r - 1) < 0 ? 0 : (r - 1);
        v3 = (r + 1) > 24 ? 24 : (r + 1);
        q3 = (q - 1) < 0 ? 0 : (q - 1);
        p3 = (p - 1) < 0 ? 0 : (p - 1);
        loop_f:
        for (f = 0; f < 3; f++) {
          loop_v:
          for (v = v1; v <= v2; v++) {
            loop_u:
            for (u = u1; u <= u2; u++) {
              loop_t:
              for (t = t1; t <= t2; t++) {
                loop_s:
                for (s = s1; s <= s2; s++) {
                  sol[r][q][p] += filter[v - r0 + 1 - 1][t - q0 + 1 - 1][f] * filter[u - p0 + 1 - 1][s - r0 + 1 - 1][f] * orig[s][t][f];
                }
              }
            }
          }
        }
      }
    }
  }
}
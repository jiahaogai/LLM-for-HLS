#pragma ACCEL kernel

void stencil3d(long C0[25][25][25],long C1[25][25][25])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  int v;
  long A0;
  long A1;
  long A2;
  long A3;
  long A4;
  long A5;
  long A6;
  long A7;
  long A8;
  r = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop_r:
  for (;;) {
    q = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_q:
    for (;;) {
      p = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loop_p:
      for (;;) {
        s = -1;
        v = 1;
        loop_v:
        for (; v <= 1; v++) {
          t = -1;
          u = 1;
          loop_u:
          for (; u <= 1; u++) {
            loop_t:
            for (; t <= 1; t++) {
              A0 = C0[r + s][q + v][p + t];
              A1 = C0[r + s][q + 0][p + t];
              A2 = C0[r + s][q - v][p + t];
              A3 = C0[r + 0][q + v][p + t];
              A4 = C0[r + 0][q + 0][p + t];
              A5 = C0[r + 0][q - v][p + t];
              A6 = C0[r - 1][q + v][p + t];
              A7 = C0[r - 1][q + 0][p + t];
              A8 = C0[r - 1][q - v][p + t];
              C1[r][q][p] = ((A0 + A1 + A2) + (A3 + A4 + A5) + (A6 + A7 + A8)) / 6;
              p++;
            }
            t = 0;
          }
        }
        s = 0;
      }
      p = 1;
    }
    q = 1;
  }
  r = 1;
}
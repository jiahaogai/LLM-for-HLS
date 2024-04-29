#pragma ACCEL kernel

void stencil3d(long C0[20][20][20],long C1[20][20][20])
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
  long B0;
  long B1;
  long B2;
  long tmp_0;
  long tmp_1;
  long tmp_2;
  long tmp_3;
  long tmp_4;
  long tmp_5;
  long tmp_6;
  long tmp_7;
  A0 = 0;
  A1 = 0;
  A2 = 0;
  B0 = 0;
  B1 = 0;
  B2 = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (v = 1; v < 20 - 1; v++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (u = 1; u < 20 - 1; u++) {
      for (t = 1; t < 20 - 1; t++) {
        A2 = C0[0][t][u] - 2 * C0[1][t][u] + C0[2][t][u];
        A1 = C0[1][t][u] - 2 * C0[2][t][u] + C0[3][t][u];
        A0 = C0[2][t][u] - 2 * C0[3][t][u] + C0[4][t][u];
        B2 = C1[0][t][u] - 2 * C1[1][t][u] + C1[2][t][u];
        B1 = C1[1][t][u] - 2 * C1[2][t][u] + C1[3][t][u];
        B0 = C1[2][t][u] - 2 * C1[3][t][u] + C1[4][t][u];
        tmp_0 = A0 + B0;
        tmp_1 = A1 + B1;
        tmp_2 = A2 + B2;
        tmp_3 = A1 + tmp_2;
        C1[4][t][u] = C1[3][t][u] + tmp_3;
        tmp_4 = tmp_1 + tmp_3;
        C1[3][t][u] = C1[2][t][u] + tmp_4;
        tmp_5 = tmp_0 + tmp_4;
        C1[2][t][u] = C1[1][t][u] + tmp_5;
        C1[1][t][u] = C1[0][t][u] + tmp_5;
        C1[0][t][u] = A0 + tmp_5;
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (u = 1; u < 20 - 1; u++) {
      for (q = 1; q < 20 - 1; q++) {
        for (p = 1; p < 20 - 1; p++) {
          C0[4][q][p] = 0.125 * (C1[4][q][p] - (C1[3][q][p] + C1[2][q][p] + C1[1][q][p] + C1[0][q][p]));
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (u = 1; u < 20 - 1; u++) {
      for (q = 1; q < 20 - 1; q++) {
        for (p = 1; p < 20 - 1; p++) {
          C0[0][q][p] = 0.125 * (C1[0][q][p] + (C1[1][q][p] + C1[2][q][p] + C1[3][q][p] + C1[4][q][p]));
        }
      }
    }
  }
}
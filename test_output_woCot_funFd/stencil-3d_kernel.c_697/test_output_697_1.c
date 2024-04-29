#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27][27][27],double sol[27][27][27])
{
  long r;
  long q;
  long p;
  long s;
  long t;
  long u;
  double B[3];
  double tmp[3];
  long tmp_x;
  long tmp_y;
  long tmp_z;
  long AI;
  double A[125];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 27; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 27; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{8}
      for (p = 0; p < 27; p++) {
        AI = 0;
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (s = -1; s <= 1; s++) {
#pragma ACCEL PARALLEL FACTOR=auto{8}
          for (t = -1; t <= 1; t++) {
#pragma ACCEL PARALLEL FACTOR=auto{8}
            for (u = -1; u <= 1; u++) {
              tmp_x = r + s;
              tmp_y = q + t;
              tmp_z = p + u;
              if (tmp_x >= 0 && tmp_x < 27 && tmp_y >= 0 && tmp_y < 27 && tmp_z >= 0 && tmp_z < 27) {
                tmp[AI] = orig[tmp_x][tmp_y][tmp_z];
              }
              else {
                tmp[AI] = 0.0;
              }
              AI++;
            }
          }
        }
        B[0] = 1.0;
        B[1] = -8.0;
        B[2] = 1.0;
        A[0] = 1.0;
        A[1] = -2.0;
        A[2] = 1.0;
        A[3] = -8.0;
        A[4] = 1.0;
        A[5] = -2.0;
        A[6] = 1.0;
        A[7] = -8.0;
        A[8] = 1.0;
        A[9] = -2.0;
        A[10] = 1.0;
        A[11] = -8.0;
        A[12] = 1.0;
        A[13] = -2.0;
        A[14] = 1.0;
        A[15] = -8.0;
        A[16] = 1.0;
        A[17] = -2.0;
        A[18] = 1.0;
        A[19] = -8.0;
        A[20] = 1.0;
        A[21] = -2.0;
        A[22] = 1.0;
        A[23] = -8.0;
        A[24] = 0.0;
        sol[r][q][p] = 0.0;
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (s = 0; s < 25; s++) {
          sol[r][q][p] += B[s] * A[s] * tmp[s];
        }
      }
    }
  }
}
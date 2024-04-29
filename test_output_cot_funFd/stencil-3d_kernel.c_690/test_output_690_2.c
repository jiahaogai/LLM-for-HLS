Code: #pragma ACCEL kernel

void stencil3d(char C0,char C1,double orig[27],double sol[27])
{
  double C2;
  double C3;
  double C4;
  double C5;
  double C6;
  double C7;
  double C8;
  double tmp[9];
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (k = 0; k < 3; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 3; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{8}
      for (i = 0; i < 3; i++) {
        tmp[0] = orig[IX(i - 1, j - 1, k - 1)];
        tmp[1] = orig[IX(i, j - 1, k - 1)];
        tmp[2] = orig[IX(i + 1, j - 1, k - 1)];
        tmp[3] = orig[IX(i - 1, j, k - 1)];
        tmp[4] = orig[IX(i, j, k - 1)];
        tmp[5] = orig[IX(i + 1, j, k - 1)];
        tmp[6] = orig[IX(i - 1, j + 1, k - 1)];
        tmp[7] = orig[IX(i, j + 1, k - 1)];
        tmp[8] = orig[IX(i + 1, j + 1, k - 1)];
        C2 = 0.5 * (tmp[2] - tmp[0]);
        C3 = 0.5 * (tmp[5] - tmp[3]);
        C4 = 0.5 * (tmp[8] - tmp[6]);
        C5 = 0.5 * (tmp[3] + tmp[5] - tmp[0] - tmp[8]);
        C6 = (tmp[6] + tmp[7] - tmp[2] - tmp[4]) / 2.0;
        C7 = 0.5 * (tmp[4] - tmp[1]);
        C8 = 0.5 * (tmp[1] + tmp[7] - tmp[6] - tmp[8]);
        sol[IX(i, j, k)] = C1 * (C2 * C4 - C3 * C5 - C6 * C7 + C8 * C5) + C0 * tmp[4];
      }
    }
  }
//#pragma endscop
}
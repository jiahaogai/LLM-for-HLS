#pragma ACCEL kernel

void stencil(char orig[25][20][3],char sol[25][20][3],char filter[3][3][3])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
  int v;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  for (r = 1; r < 24; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 20; q++) {
      for (p = 1; p < 3; p++) {
        for (s = 0; s < 3; s++) {
          for (t = 0; t < 3; t++) {
            sol[r][q][p] += filter[s][t][p] * orig[r][q + s][t];
          }
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      for (p = 1; p < 3; p++) {
        for (s = 0; s < 3; s++) {
          for (t = 0; t < 3; t++) {
            sol[r][q][p] += filter[s][t][p] * orig[r][q + s][t];
          }
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 1; q < 20; q++) {
      for (p = 0; p < 3; p++) {
        for (s = 0; s < 3; s++) {
          for (t = 0; t < 3; t++) {
            sol[r][q][p] += filter[s][t][p] * orig[r][q + s][t];
          }
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      for (p = 0; p < 3; p++) {
        for (s = 0; s < 3; s++) {
          for (t = 0; t < 3; t++) {
            sol[r][q][p] += filter[s][t][p] * orig[r][q + s][t];
          }
        }
      }
    }
  }
//#pragma endscop
}
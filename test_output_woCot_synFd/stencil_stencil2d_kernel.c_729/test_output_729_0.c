#pragma ACCEL kernel

void stencil(double orig[4][4],double sol[4][4],double filter[3][3])
{
  int i;
  int j;
  int k;
  int l;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 3; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{32}
        for (l = 0; l < 3; l++) {
          sol[i][j] += filter[k][l] * orig[i + k - 1][j + l - 1];
        }
      }
    }
  }
//#pragma endscop
}
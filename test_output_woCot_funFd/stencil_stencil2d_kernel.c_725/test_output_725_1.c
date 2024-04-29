However, since the function is intended for hardware acceleration, the tool is free to make trade-offs between performance and area in order to satisfy the directives and produce a hardware implementation that satisfies the function's specification.

#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  int k;
  int l;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 4; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = -1; k <= 1; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (l = -1; l <= 1; l++) {
          sol[i][j] += filter[k + 1][l + 1] * orig[i + k][j + l];
        }
      }
    }
  }
//#pragma endscop
}
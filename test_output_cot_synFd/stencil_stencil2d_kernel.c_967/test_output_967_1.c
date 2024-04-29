#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    inner:
    for (j = 0; j < 4; j++) {
      int sum = 0;
      int ki;
      int kj;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_ki:
      for (ki = 0; ki < 3; ki++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_kj:
        for (kj = 0; kj < 3; kj++) {
          sum += filter[ki][kj] * orig[i + ki - 1][j + kj - 1];
        }
      }
      sol[i][j] = sum;
    }
  }
}
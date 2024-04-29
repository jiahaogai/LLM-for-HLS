#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int k;
  int l;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = i - 1; k <= i + 1; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        for (l = j - 1; l <= j + 1; l++) {
          if ((((k >= 0) && (k < 4)) && ((l >= 0) && (l < 4))) && ((k != i) || (l != j))) {
            sol[i][j] += orig[k][l] * filter[k - i + 1][l - j + 1];
          }
        }
      }
    }
  }
//#pragma endscop
}
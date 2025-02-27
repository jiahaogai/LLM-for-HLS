#pragma ACCEL PIPELINE auto{off}
 
 #pragma ACCEL TILE FACTOR=auto{1}
 
 #pragma ACCEL PARALLEL FACTOR=auto{3}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8188; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = -4; k <= 4; k++) {
        sum += filter[4 + k] * orig[i + k][j];
      }
      sol[i][j] = sum;
    }
  }
}
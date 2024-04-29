#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int k;
  int m;
  int n;
  int pad_size = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  pad_clamp((int *)orig,400,400,pad_size,1);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 400 - 2 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 400 - 2 + 1; j++) {
      sol[i][j] = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 3; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (m = 0; m < 3; m++) {
          sol[i][j] += filter[k * 3 + m] * orig[i + k][j + m];
        }
      }
    }
  }
  pad_clamp((int *)sol,400,400,pad_size,-1);
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int curr;
  int fltr;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 32 + 1 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 32 + 1 - 1; j++) {
      curr = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        fltr = filter[k];
        curr += fltr * orig[i + (k - 4) / 2][j + (k - 4) % 2];
      }
      sol[i][j] = curr;
    }
  }
}
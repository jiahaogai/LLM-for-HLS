#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 1; j < 8191; j++) {
      tmp = 0;
      t = 48;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4; k <= 4; k++) {
        tmp += ((int )filter[t]) * orig[i + k + 1];
        t--;
      }
      sol[j] = tmp;
    }
    sol[8192] = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      tmp = sol[j];
      sol[j] = sol[j + 1];
      sol[j + 1] = tmp;
    }
  }
}
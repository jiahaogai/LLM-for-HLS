Code: 
#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{2}
#pragma ACCEL PARALLEL FACTOR=auto{14}

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + (-4 + k) * 8192] [j + (-4 + k) * 8192];
      }
      sol[i * 8192 + j] = sum;
    }
  }
}
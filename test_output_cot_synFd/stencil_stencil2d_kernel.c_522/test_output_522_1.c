Code: #pragma ACCEL kernel


#pragma ACCEL PIPELINE auto{flatten}


#pragma ACCEL TILE FACTOR=auto{4}


#pragma ACCEL PARALLEL FACTOR=auto{2}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int x;
  int y;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      idx = i * 8190 + j;
      sol[idx] = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        x = i - 4 + ((k % 3) - 1);
        y = j - 4 + ((k / 3) - 1);
        sol[idx] += filter[k] * orig[x * 8190 + y];
      }
    }
  }
}
#pragma ACCEL kernel

int main()
{
  int orig[8192];
  int sol[8192];
  int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (int i = 0; i < 8192; i++) 
    orig[i] = i;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (int i = 0; i < 8192; i++) {
    sol[i] = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (int j = 0; j < 9; j++) {
      int tmp_var;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      tmp_var = orig[i - 4 + j] * filter[j];
      sol[i] += tmp_var;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (int i = 0; i < 8192; i++) {
    if (sol[i] < 0) {
      sol[i] = 0;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (int i = 0; i < 8192; i++) {
    if (sol[i] > 255) {
      sol[i] = 255;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (int i = 0; i < 8192; i++) {
    orig[i] = sol[i];
  }
}
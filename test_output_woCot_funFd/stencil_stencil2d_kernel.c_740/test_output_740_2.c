#pragma ACCEL kernel

int main()
{
  int orig[8192];
  int sol[8192];
  int filter[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  
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
      int tmp_tmp;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      tmp_tmp = orig[i - 4 + j];
      sol[i] += filter[j] * tmp_tmp;
    }
  }
}
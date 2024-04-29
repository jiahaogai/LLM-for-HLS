#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      buf = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k_col = 0; k_col < 9; k_col++) {
        k = i - 4 + k_col;
        if (k < 0 || k > 8191) {
          buf = 0;
        }
         else {
          buf += filter[k_col] * orig[k * 8192 + j];
        }
      }
      sol[i * 8192 + j] = buf;
    }
  }
}
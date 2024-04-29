#pragma ACCEL kernel

int main()
{
  int i;
  int j;
  int k;
  int orig[8192];
  int sol[8192];
  int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_array:
  for (i = 0; i < 8192; i++) {
    orig[i] = i;
    sol[i] = 0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  stencil:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 8; j++) {
      int sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        int i_k = i * 8 + k - 4;
        int j_k = j * 8 + k - 4;
        if (i_k >= 0 && i_k < 8192 && j_k >= 0 && j_k < 8192) {
          sum += orig[i_k] * filter[k];
        }
      }
      sol[i * 8 + j] = sum;
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  verify:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 8; j++) {
      if (sol[i * 8 + j] != ((255 * 9) - ((i * 8 - 1) + (j * 8 - 1)))) {
        return 1;
      }
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  return 0;
}
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_orig;
  int tmp_sol;
  int index_orig;
  int index_sol;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      tmp_orig = 0;
      tmp_sol = 0;
      inner:
      for (k = 0; k < 9; k++) {
        index_orig = (i - 4 + ((k + 4) >> 5)) * 256 + j - 4 + ((k + 4) & 31);
        if (index_orig < 0 || index_orig > 8191) {
          tmp_orig = 0;
        }
         else {
          tmp_orig = orig[index_orig];
        }
        tmp = filter[k] * tmp_orig;
        tmp_sol += tmp;
      }
      index_sol = i * 256 + j;
      sol[index_sol] = tmp_sol;
    }
  }
}
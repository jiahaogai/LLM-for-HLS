#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 9; j++) {
      buf = 0;
      
#pragma ACCEL PARALLEL reduction=buf FACTOR=auto{1}
      inner:
      for (k = 0; k < 8; k++) {
        k_col = i - 4 + k;
        buf += orig[k_col] * filter[j * 8 + k];
      }
      sol[i] = buf;
    }
  }
}
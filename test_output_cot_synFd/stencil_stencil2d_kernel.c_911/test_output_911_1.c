#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 256; j++) {
      buf = 0;
      
#pragma ACCEL PARALLEL reduction=buf FACTOR=auto{1}
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        k = i - 4 + k_col;
        if ((((k >= 0) && (k < 256))) && ((j >= 0) && (j < 256))) {
          buf += orig[k * 256 + j] * filter[k_col];
        }
      }
      sol[i * 256 + j] = buf;
    }
  }
}
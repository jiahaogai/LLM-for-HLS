#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 8; j++) {
      buf = 0;
      
#pragma ACCEL PARALLEL reduction=buf FACTOR=auto{8}
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        k = i * 8 + k_col;
        buf += orig[k] * filter[k_col];
      }
      sol[i * 8 + j] = buf;
    }
  }
}
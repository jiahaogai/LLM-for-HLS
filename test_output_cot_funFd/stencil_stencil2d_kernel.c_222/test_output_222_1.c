#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int index;
  int flatten_index;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      flatten_index = i * 256 + j;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      stencil_label1:
      for (k = -4; k < 5; k++) {
        index = flatten_index + k;
        if (((i + k) >= 0) && ((i + k) < 256)) {
          if(((j + k) >= 0) && ((j + k) < 256)) {
            t += filter[k + 4] * orig[index];
          }
        }
      }
      sol[flatten_index] = t;
    }
  }
}
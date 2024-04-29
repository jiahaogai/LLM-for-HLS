#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int bound;
  int flatten_i;
  int flatten_j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      bound = (256 + 8 - 1);
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      inner:
      for (k = -8; k < 8 + 1; k++) {
        if ((k < -8 || k > 8)) {
          flatten_i = i * 4 + k;
          if (flatten_i > bound) {
            flatten_i = bound;
          }
          flatten_i = flatten_i - 8;
          if (flatten_i < 0) {
            flatten_i = 0;
          }
          flatten_j = j * 4 + k;
          if (flatten_j > bound) {
            flatten_j = bound;
          }
          flatten_j = flatten_j - 8;
          if (flatten_j < 0) {
            flatten_j = 0;
          }
          sol[idx] = orig[flatten_i * 256 + flatten_j] * filter[k + 8];
        }
      }
    }
  }
}
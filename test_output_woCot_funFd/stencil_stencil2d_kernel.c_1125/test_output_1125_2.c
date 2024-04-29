#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 64; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      stencil_label2:
      for (k = -4; k < 5; k++) {
        int cur;
        int flatten_id;
        flatten_id = 0;
        cur = orig[((((i + pad) * 64) + ((j + pad) * 1)) + k)];
        t += filter[((8 - 1) + flatten_id)] * cur;
      }
      sol[((i * 64) + j)] = t;
    }
  }
}
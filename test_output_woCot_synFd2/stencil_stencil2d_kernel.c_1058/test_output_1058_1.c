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
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -4; k < 5; k++) {
        int _in;
        int _out;
        _in = orig[((pad + i * 64) + k) * 64 + (pad + j * 64)];
        _out = _in + filter[k + 4];
        t = _out;
      }
      sol[i * 64 + j * 16] = t;
    }
  }
}
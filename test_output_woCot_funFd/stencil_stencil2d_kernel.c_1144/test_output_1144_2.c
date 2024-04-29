- It performs data alignment to avoid penalties caused by memory alignment.
- It prevents overflow and underflow at the loop boundaries to avoid erroneous results.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -4; k < 5; k++) {
        int _in;
        int _out;
        _in = orig[((((pad + i) * 64) + ((pad + j) * 8)) + k)];
        _out = _in + filter[((k + 4) * 8) + 4];
        t = _out;
      }
      sol[(((pad + i) * 64) + ((pad + j) * 8)) + 0] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -3; k < 5; k++) {
        int _in;
        int _out;
        _in = orig[((((pad + i) * 64) + ((pad + j) * 8)) + k)];
        _out = _in + filter[((k + 3) * 8) + 4];
        t = _out + t;
      }
      sol[(((pad + i) * 64) + ((pad + j) * 8)) + 1] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -2; k < 5; k++) {
        int _in;
        int _out;
        _in = orig[((((pad + i) * 64) + ((pad + j) * 8)) + k)];
        _out = _in + filter[((k + 2) * 8) + 4];
        t = _out + t;
      }
      sol[(((pad + i) * 64) + ((pad + j) * 8)) + 2] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = -1; k < 5; k++) {
        int _in;
        int _out;
        _in = orig[((((pad + i) * 64) + ((pad + j) * 8)) + k)];
        _out = _in + filter[((k + 1) * 8) + 4];
        t = _out + t;
      }
      sol[(((pad + i) * 64) + ((pad + j) * 8)) + 3] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{4}
      for (k = 0; k < 5; k++) {
        int _in;
        int _out;
        _in = orig[((((pad + i) * 64) + ((pad + j) * 8)) + k)];
        _out = _in + filter[(k * 8) + 4];
        t = _out + t;
      }
      sol[(((pad + i) * 64) + ((pad + j) * 8)) + 4] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = 1; k < 5; k++) {
        int _in;
        int _out;
        _in = orig[((((pad + i) * 64) + ((pad + j) * 8)) + k)];
        _out = _in + filter[((k - 1) * 8) + 4];
        t = _out + t;
      }
      sol[(((pad + i) * 64) + ((pad + j) * 8)) + 5] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = 2; k < 5; k++) {
        int _in;
        int _out;
        _in = orig[((((pad + i) * 64) + ((pad + j) * 8)) + k)];
        _out = _in + filter[((k - 2) * 8) + 4];
        t = _out + t;
      }
      sol[(((pad + i) * 64) + ((pad + j) * 8)) + 6] = t;
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      for (k = 3; k < 5; k++) {
        int _in;
        int _out;
        _in = orig[((((pad + i) * 64) + ((pad + j) * 8)) + k)];
        _out = _in + filter[((k - 3) * 8) + 4];
        t = _out + t;
      }
      sol[(((pad + i) * 64) + ((pad + j) * 8)) + 7] = t;
    }
  }
}
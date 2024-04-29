Code: #pragma ACCEL kernel
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  int flit;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{62}
  stencil_label1:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    stencil_label2:
    for (j = 0; j < 256; j++) {
      t = 0;
      int stencil_label3;
      stencil_label3:
      for (k = -4; k < 5; k++) {
        int _in;
        int _out;
        _in = orig[((i + 4) + ((j + 4) * 256)) + (k * 256)];
        _out = 0;
        int filter_label;
        filter_label:
        for (flit = 0; flit < 9; flit++) {
          _out += filter[flit] * _in[((4 - k) * 256) + flit];
        }
        t += _out;
      }
      sol[((i + 4) + (j * 256)) ] = t;
    }
  }
}
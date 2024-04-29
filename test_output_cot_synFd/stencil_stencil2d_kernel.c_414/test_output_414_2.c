#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int idx0;
  int flatten_i;
  int flatten_j;
  int bound;
  int _in_;
  int _out_;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      idx0 = i * 256 + j;
      _out_ = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (tj = -4; tj <= 4; tj++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_2:
        for (ti = -4; ti <= 4; ti++) {
          bound = (256 + 4) * (1 + 4);
          if (((ti + 4) < 0) || ((ti + 4) >= 256) || ((tj + 4) < 0) || ((tj + 4) >= 256)) {
            _in_ = 0;
          }
           else {
            idx = (4 + (tj + 4)) * bound + (4 + (ti + 4));
            _in_ = orig[idx];
          }
          _out_ += _in_ * filter[tj * 9 + ti];
        }
      }
      sol[idx0] = _out_;
    }
  }
}
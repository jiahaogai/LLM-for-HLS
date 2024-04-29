#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int oidx;
  int flatten_id_0;
  int flatten_id_1;
  int _in_idx_;
  int _out_idx_;
  int filter_idx;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      oidx = idx;
      flatten_id_0 = 0 + 1 * 4;
      flatten_id_1 = 1 + 1 * 4;
      _in_idx_ = oidx - 1;
      if (_in_idx_ < 0) {
        _in_idx_ = 0;
      }
      _out_idx_ = flatten_id_0;
      sol[oidx] = orig[oidx] + ((filter[0] * orig[idx]) + (filter[1] * orig[_in_idx_]) + (filter[2] * orig[idx + 1]) + (filter[3] * orig[oidx - 1]) + (filter[4] * orig[idx - 1]) + (filter[5] * orig[oidx + 1]) + (filter[6] * orig[idx + 1]) + (filter[7] * orig[oidx - 1 - 256]) + (filter[8] * orig[idx - 1 - 256]));
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 1; k < 4; k++) {
        _in_idx_ = oidx - 1 - k*256;
        if (_in_idx_ < 0) {
          _in_idx_ = 0;
        }
        _out_idx_ = flatten_id_1 + k;
        sol[oidx] += filter[k] * orig[_in_idx_];
      }
    }
  }
}
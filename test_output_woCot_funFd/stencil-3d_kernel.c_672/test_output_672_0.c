#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long _in_i;
  long _in_j;
  long _in_k;
  long _out_i;
  long _out_j;
  long _out_k;
  long _tmp_0;
  long _tmp_1;
  long _tmp_2;
  long _tmp_3;
  long _tmp_4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
  for (j = 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
    for (k = 1; k < 32 + 1; k++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32 + 1; i++) {
        _in_i = 32 + 1;
        _in_j = j;
        _in_k = k;
        _out_i = i;
        _out_j = j;
        _out_k = k;
        _tmp_0 = orig[_out_i * _out_j * _out_k];
        _tmp_1 = orig[_out_i * _out_j * _out_k + _out_k];
        _tmp_2 = orig[_out_i * _out_j * _out_k + _out_j * _out_k];
        _tmp_3 = orig[_out_i * _out_j * _out_k + _out_j * _out_k + _out_k];
        _tmp_4 = (_tmp_1 + _tmp_2) + _tmp_3;
        sol[_out_i * _out_j * _out_k] = ((_tmp_4 + _tmp_0) / C0);
      }
    }
  }
}
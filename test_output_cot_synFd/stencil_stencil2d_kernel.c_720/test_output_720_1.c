#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{126}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  int end;
  int _in_orig[8192];
  int _in_sol[8192];
  int _in_filter[9];
  int _out_sol[8192];
  
#pragma ACCEL array=_in_orig size=8192
  
#pragma ACCEL array=_in_sol size=8192
  
#pragma ACCEL array=_in_filter size=9
  
#pragma ACCEL array=_out_sol
  for (i = 0; i < 8192; i++) {
    _in_orig[i] = orig[i];
    _in_sol[i] = sol[i];
    _in_filter[0] = filter[0];
    _in_filter[1] = filter[1];
    _in_filter[2] = filter[2];
    _in_filter[3] = filter[3];
    _in_filter[4] = filter[4];
    _in_filter[5] = filter[5];
    _in_filter[6] = filter[6];
    _in_filter[7] = filter[7];
    _in_filter[8] = filter[8];
    idx = i % 27;
    end = 27 + (-27 + 1);
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    val = 0;
    
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
    for (j = 0; j < 27; j++) {
      val += _in_orig[((i / 27) * 27) + j] * _in_filter[idx + j];
    }
    _out_sol[i] = val;
  }
  for (i = 0; i < 8192; i++) {
    sol[i] = _out_sol[i];
  }
}
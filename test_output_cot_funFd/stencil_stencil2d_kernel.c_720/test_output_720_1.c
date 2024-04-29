#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{126}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
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
  int _out_sol[8192];
  
#pragma ACCEL array=_in_orig dimension=8192
  
#pragma ACCEL array=_in_sol dimension=8192
  
#pragma ACCEL array=_out_sol dimension=8192
  end = 8192;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    _in_orig[i] = orig[i];
    _in_sol[i] = sol[i];
    _out_sol[i] = 0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  int _val_filter[9];
  
#pragma ACCEL array=_val_filter
  for (i = 0; i < 9; i++) {
    _val_filter[i] = filter[i];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 4; i < 8192 - 4; i++) {
    val = 0;
    
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{8}
    for (j = 0; j < 9; j++) {
      idx = i - 4 + j;
      val += _val_filter[j] * _in_orig[idx];
    }
    _out_sol[i] = val;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sol[i] = _out_sol[i];
  }
}
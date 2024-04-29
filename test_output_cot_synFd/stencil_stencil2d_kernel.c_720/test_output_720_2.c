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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8186; j++) {
      idx = (8190 * (j - 1)) + i;
      val = ((orig[idx - 8190] + orig[idx]) + orig[idx + 8190]) + ((orig[idx - 1] + orig[idx + 1]) + orig[idx + 8186]) + ((orig[idx - 8186] + orig[idx + 8186]));
      sol[idx] = val;
    }
  }
/* Standardize from: for(i = 1; i < 8192 - 8; i++) {...} */
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  i = 8;
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  while (i < 8192 - 8) {
    int _in_j_0 = 1;
    int _in_j_1 = 8186;
    int _upper_bound_j = 8186;
    int _lower_bound_j = 1;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = _in_j_0; j <= _upper_bound_j; j++) {
      int _in_k = 1;
      int _upper_bound_k = 8;
      int _lower_bound_k = 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = _in_k; k <= _upper_bound_k; k++) {
        idx = (8190 * (_lower_bound_j + 0)) + (_lower_bound_k + 0);
        sol[idx] = filter[0] * orig[idx] + filter[1] * (orig[idx + 1] + orig[idx - 1]) + filter[2] * (orig[idx + 8190] + orig[idx - 8190]) + filter[3] * (orig[idx + 8186] + orig[idx - 8186]) + filter[4] * (orig[idx + 1 + 8186] + orig[idx - 1 - 8186] + orig[idx + 8190 + 8186] + orig[idx - 8190 - 8186]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = _lower_bound_j + 1; j < _upper_bound_j; j++) {
      int _in_k = 2;
      int _upper_bound_k = 8;
      int _lower_bound_k = 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = _in_k; k <= _upper_bound_k; k++) {
        idx = (8190 * (j - 0)) + (k - 0);
        sol[idx] = filter[1] * (orig[idx + 1] + orig[idx - 1]) + filter[2] * (orig[idx + 8190] + orig[idx - 8190]) + filter[3] * (orig[idx + 8186] + orig[idx - 8186]) + filter[4] * (orig[idx + 1 + 8186] + orig[idx - 1 - 8186] + orig[idx + 8190 + 8186] + orig[idx - 8190 - 8186]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = _upper_bound_j - 1; j >= _lower_bound_j + 1; j--) {
      int _in_k = 0;
      int _upper_bound_k = 7;
      int _lower_bound_k = 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = _upper_bound_k; k >= _lower_bound_k; k--) {
        idx = (8190 * (j - 0)) + (k - 0);
        sol[idx] = filter[0] * orig[idx] + filter[1] * (orig[idx + 1] + orig[idx - 1]) + filter[2] * (orig[idx + 8190] + orig[idx - 8190]) + filter[3] * (orig[idx + 8186] + orig[idx - 8186]) + filter[4] * (orig[idx + 1 + 8186] + orig[idx - 1 - 8186] + orig[idx + 8190 + 8186] + orig[idx - 8190 - 8186]);
      }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = _lower_bound_j; j >= 1; j--) {
      int _in_k = 0;
      int _upper_bound_k = 7;
      int _lower_bound_k = 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = _lower_bound_k; k <= _upper_bound_k; k++) {
        idx = (8190 * (j - 0)) + (k - 0);
        sol[idx] = filter[0] * orig[idx] + filter[1] * (orig[idx + 1] + orig[idx - 1]) + filter[2] * (orig[idx + 8190] + orig[idx - 8190]) + filter[3] * (orig[idx + 8186] + orig[idx - 8186]) + filter[4] * (orig[idx + 1 + 8186] + orig[idx - 1 - 8186] + orig[idx + 8190 + 8186] + orig[idx - 8190 - 8186]);
      }
    }
    i += 8186;
  }
}
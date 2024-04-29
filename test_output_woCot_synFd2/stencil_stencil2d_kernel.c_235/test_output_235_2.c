#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int orig_row_idx;
  int sol_row_idx;
  int lower_row_idx;
  int upper_row_idx;
  int orig_col_idx;
  int sol_col_idx;
  int lower_col_idx;
  int upper_col_idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 1; i < 33; i++) {
      orig_row_idx = 33 * (j - 1);
      sol_row_idx = 33 * j;
      orig_col_idx = 33 * (i - 1);
      sol_col_idx = 33 * i;
      center = orig[orig_row_idx + orig_col_idx];
      lower_row_idx = orig_row_idx - 1;
      upper_row_idx = orig_row_idx + 1;
      lower_col_idx = orig_col_idx - 1;
      upper_col_idx = orig_col_idx + 1;
      idx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        if (((lower_row_idx >= 0 ? lower_row_idx : 0) <= 
             (upper_row_idx <= 8191 ? upper_row_idx : 8191)) && ((lower_col_idx 
                 >= 0 ? lower_col_idx : 0) <=  (upper_col_idx <= 8191 ? 
                                                 upper_col_idx : 8191))) {
          sol[sol_row_idx + sol_col_idx] += filter[k] * orig[lower_row_idx + 
            lower_col_idx];
        }
        if (((lower_row_idx >= 0 ? lower_row_idx : 0) <= 
             (upper_row_idx <= 8191 ? upper_row_idx : 8191)) && ((lower_col_idx 
                 < 0 ? 0 : lower_col_idx) <=  (upper_col_idx <= 8191 ? 
                                                upper_col_idx : 8191))) {
          sol[sol_row_idx + sol_col_idx] += filter[k] * orig[lower_row_idx + 
            upper_col_idx];
        }
        if (((lower_row_idx >= 0 ? lower_row_idx : 0) <= 
             (upper_row_idx <= 8191 ? upper_row_idx : 8191)) && ((lower_col_idx 
                 > 8191 ? 8191 : lower_col_idx) <=  (upper_col_idx <= 8191 ? 
                                                     upper_col_idx : 8191))) {
          sol[sol_row_idx + sol_col_idx] += filter[k] * orig[lower_row_idx + 
            lower_col_idx];
        }
        if (((lower_row_idx >= 0 ? lower_row_idx : 0) <= 
             (upper_row_idx <= 8191 ? upper_row_idx : 8191)) && ((lower_col_idx 
                 <= 0 ? 0 : lower_col_idx) <=  (upper_col_idx <= 8191 ? 
                                                 upper_col_idx : 8191))) {
          sol[sol_row_idx + sol_col_idx] += filter[k] * orig[lower_row_idx + 
            upper_col_idx];
        }
        if (((upper_row_idx <= 8191 ? upper_row_idx : 8191) < 
             (lower_row_idx >= 0 ? lower_row_idx : 0)) && ((lower_col_idx >= 
                0 ? lower_col_idx : 0) <=  (upper_col_idx <= 8191 ? 
                                             upper_col_idx : 8191))) {
          sol[sol_row_idx + sol_col_idx] += filter[k] * orig[upper_row_idx + 
            lower_col_idx];
        }
        if (((upper_row_idx <= 8191 ? upper_row_idx : 8191) < 
             (lower_row_idx >= 0 ? lower_row_idx : 0)) && ((lower_col_idx >= 
                0 ? lower_col_idx : 0) <=  (upper_col_idx <= 8191 ? 
                                             upper_col_idx : 8191))) {
          sol[sol_row_idx + sol_col_idx] += filter[k] * orig[upper_row_idx + 
            upper_col_idx];
        }
        if (((upper_row_idx <= 8191 ? upper_row_idx : 8191) < 
             (lower_row_idx >= 0 ? lower_row_idx : 0)) && ((lower_col_idx >= 
                0 ? lower_col_idx : 0) <=  (upper_col_idx <= 8191 ? 
                                             upper_col_idx : 8191))) {
          sol[sol_row_idx + sol_col_idx] += filter[k] * orig[upper_row_idx + 
            lower_col_idx];
        }
        if (((upper_row_idx <= 8191 ? upper_row_idx : 8191) < 
             (lower_row_idx >= 0 ? lower_row_idx : 0)) && ((lower_col_idx >= 
                8191 ? 8191 : lower_col_idx) <=  (upper_col_idx <= 8191 ? 
                                                   upper_col_idx : 8191))) {
          sol[sol_row_idx + sol_col_idx] += filter[k] * orig[upper_row_idx + 
            lower_col_idx];
        }
        if (((upper_row_idx <= 8191 ? upper_row_idx : 8191) < 
             (lower_row_idx >= 0 ? lower_row_idx : 0)) && ((lower_col_idx >= 
                8191 ? 8191 : lower_col_idx) <=  (upper_col_idx <= 8191 ? 
                                                   upper_col_idx : 8191))) {
          sol[sol_row_idx + sol_col_idx] += filter[k] * orig[upper_row_idx + 
            upper_col_idx];
        }
        idx++;
      }
    }
  }
}
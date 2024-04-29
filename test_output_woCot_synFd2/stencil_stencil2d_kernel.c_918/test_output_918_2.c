Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flatten_index;
  int value;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loopj:
/* Standardize from: for(j = 1; j < 33 + 1 - 2; j++) {...} */
  for (j = 1 + 32; j < 33 + 1 - 2; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1; k < 33 + 1 - 2; k++) {...} */
    for (k = 1 + 32; k < 33 + 1 - 2; k++) {
      i_col = 1 - 2 * (1 + 32);
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk_col:
/* Standardize from: for(k_col = 1; k_col < 3 + 1; k_col++) {...} */
      for (k_col = 1; k_col < 3 + 1; k_col++) {
        j_col = 1 - 2 * (1 + 32);
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        loopj_col:
/* Standardize from: for(j_col = 1; j_col < 3 + 1; j_col++) {...} */
        for (j_col = 1; j_col < 3 + 1; j_col++) {
          i = k_col - 1 + 1 + (3 - 2) + (33 * (j_col - 1 + 1 + (3 - 2) + (33 * (k - 1 + 1 + (3 - 2)))));
          flatten_index = (((33 + 1 - 2) * (k - 1 + 1 + 1)) + (j_col - 1 + 1)) + ((33 + 1 - 2) * (1 + 32));
          value = orig[flatten_index];
          loopk_filter:
/* Standardize from: for(k_filter = 0; k_filter < 3; k_filter++) {...} */
          for (k_filter = 0; k_filter < 3; k_filter++) {
            
#pragma ACCEL PIPELINE auto{off}
            
#pragma ACCEL TILE FACTOR=auto{1}
            
#pragma ACCEL PARALLEL FACTOR=auto{1}
            loopj_filter:
/* Standardize from: for(j_filter = 0; j_filter < 3; j_filter++) {...} */
            for (j_filter = 0; j_filter < 3; j_filter++) {
              sol[i] += filter[(((k_filter) * 3) + j_filter)] * value;
            }
          }
        }
        j_col = 3 + 1 - 2;
      }
      k_col = 3 + 1 - 2;
    }
    k = 3 + 1 - 2;
  }
}
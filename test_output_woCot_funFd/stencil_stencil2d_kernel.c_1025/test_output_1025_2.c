Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int min_i;
  int max_i;
  int min_j;
  int max_j;
  int range;
  int center;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_j:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j <= 8192 - 2; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_i:
    for (i = 1; i <= 8192 - 2; i++) {
      min_i = (i < 8192 - 2 ? i : 8192 - 2);
      max_i = (i > 1 ? i : 1);
      min_j = (j < 8192 - 2 ? j : 8192 - 2);
      max_j = (j > 1 ? j : 1);
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      range = ((8192 - 2 + 1) - 1);
      center = ((range + 1) / 2);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
      for (k = -1; k <= 1; k++) {
        if ((k == -1 || k == 1)) {
          
#pragma ACCEL PIPELINE auto{flatten}
          
#pragma ACCEL TILE FACTOR=auto{1}
          loop_jj:
          for (jj = min_j; jj <= max_j; jj++) {
            
#pragma ACCEL PIPELINE auto{off}
            
#pragma ACCEL TILE FACTOR=auto{1}
            loop_ii:
            for (ii = min_i; ii <= max_i; ii++) {
              t += filter[center + k] * orig[ii + 8192 * jj];
            }
          }
        }
      }
      sol[i + 8192 * j] = t;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int min_i;
  int max_i;
  int min_j;
  int max_j;
  int range;
  int center;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_j:
/* Standardize from: for(j = 1;j < 8192 - 1;j++) {...} */
  for (j = 1; j <= 8192 - 2; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_i:
    for (i = 1; i <= 8192 - 2; i++) {
      min_i = (i < 8192 - 2 ? i : 8192 - 2);
      max_i = (i > 1 ? i : 1);
      min_j = (j < 8192 - 2 ? j : 8192 - 2);
      max_j = (j > 1 ? j : 1);
      t = 0
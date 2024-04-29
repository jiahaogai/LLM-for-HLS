Code: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flatten_i;
  int flatten_j;
  int flatten_k;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      flatten_i = i * 256;
      flatten_j = j * 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 20; k++) {
        k_col = k * 256;
        i_col = flatten_i + k_col;
        sol[i_col] = 0.0;
        
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
	for (j_col = flatten_j; j_col < flatten_j + 1; j_col++) {
          sol[i_col] += filter[k] * orig[j_col];
        }
      }
    }
  }
}
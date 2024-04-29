#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_i;
  int flatten_j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 256; j++) {
      row = i * 256;
      col = j * 16;
      flatten_i = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 8; k++) {
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
	for (flatten_j = 0; flatten_j < 16; flatten_j++) {
          int val;
          val = orig[row + flatten_i * 16 + flatten_j] * filter[k] + sol[row + flatten_i * 16 + flatten_j] * filter[k];
          sol[row + flatten_i * 16 + flatten_j] = val;
	}
	flatten_i = 1;
      }
    }
  }
}
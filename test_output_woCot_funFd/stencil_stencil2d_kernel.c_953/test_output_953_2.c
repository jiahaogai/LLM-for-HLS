Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2; j++) {
      idx = i * 128 + j;
      center = orig[idx];
      flatten_idx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 5; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
	fast:
	for (jj = 0; jj < 5; jj++) {
          int tmp_flatten_idx = flatten_idx + jj * 9;
          sol[idx] += filter[tmp_flatten_idx] * center;
        }
	flatten_idx += 64;
      }
    }
  }
}
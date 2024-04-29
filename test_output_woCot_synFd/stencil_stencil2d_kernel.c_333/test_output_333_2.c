#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 256; j++) {
      row = i * 256;
      col = j * 256;
      flatten_row = i * 32 - 1;
      flatten_col = j * 32 - 1;
      idx = row + col;
      val = orig[idx] + ((filter[0] * (orig[idx - 1 + col])) + (filter[1] * (orig[idx + 1 + col])) + (filter[2] * (orig[idx - 2 + col] + orig[idx + 2 + col])) + (filter[3] * (orig[idx - 3 + col] + orig[idx + 3 + col])) + (filter[4] * (orig[idx - 4 + col] + orig[idx + 4 + col])) + (filter[5] * (orig[idx - 5 + col] + orig[idx + 5 + col])) + (filter[6] * (orig[idx - 6 + col] + orig[idx + 6 + col])) + (filter[7] * (orig[idx - 7 + col] + orig[idx + 7 + col])) + (filter[8] * (orig[idx - 8 + col] + orig[idx + 8 + col])));
      sol[idx] = val;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 1; k < 32; k++) {
        idx = row + col + k;
        val = orig[idx] + ((filter[0] * sol[idx - 1]) + (filter[1] * sol[idx + 1]) + (filter[2] * (sol[idx - 2] + sol[idx + 2])) + (filter[3] * (sol[idx - 3] + sol[idx + 3])) + (filter[4] * (sol[idx - 4] + sol[idx + 4])) + (filter[5] * (sol[idx - 5] + sol[idx + 5])) + (filter[6] * (sol[idx - 6] + sol[idx + 6])) + (filter[7] * (sol[idx - 7] + sol[idx + 7])) + (filter[8] * (sol[idx - 8] + sol[idx + 8])));
        sol[idx] = val;
      }
    }
  }
}
#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{31}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int bound;
  int flatten_i;
  int flatten_j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 128 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 64 + 1; j++) {
      idx = i * 64 + j;
      center = orig[idx];
      bound = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{32}
      for (k = 0; k < 9; k++) {
        flatten_i = i + ((0 + (k / 3)) - 1);
        flatten_j = j + ((k % 3) - 1);
        if (flatten_i > 0 && flatten_i <= 128 + 1 && flatten_j > 0 && flatten_j <= 64 + 1) {
          bound += filter[k] * orig[flatten_i * 64 + flatten_j];
        }
      }
      sol[idx] = bound;
    }
  }
}
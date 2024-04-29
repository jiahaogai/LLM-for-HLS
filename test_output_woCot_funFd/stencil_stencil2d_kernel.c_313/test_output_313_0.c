#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int bound;
  int tmp_orig[8];
  int tmp_sol[8];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sol[i] = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j <= 8; j++) {
      sol[i] += filter[j] * orig[i + (-4 + j)];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    if (i == 0) {
      bound = 8;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    else if (i >= 8192 - 8) {
      bound = 8192 - i;
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    else {
      bound = 1;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < bound; j++) {
      tmp_orig[j] = orig[i + j];
      tmp_sol[j] = sol[i + j];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < bound; j++) {
      orig[i + j] = tmp_sol[j];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = bound; j < 8; j++) {
      orig[i + j] = 0;
    }
  }
}
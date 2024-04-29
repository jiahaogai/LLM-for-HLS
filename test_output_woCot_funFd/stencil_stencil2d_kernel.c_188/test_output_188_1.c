5. `orig`: Input array.
6. `sol`: Output array.
7. `filter`: Filter array.

#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{126}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int flt;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  loopj:
  for (j = 0; j < 32; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 0; k < 32; k++) {
      sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopflt:
      for (flt = 0; flt < 9; flt++) {
        sum += filter[flt] * orig[((j + 2 - 1) * 32 + k + 2 - 1) * 32 + flt - 1];
      }
      sol[j * 32 + k] = sum;
    }
  }
}
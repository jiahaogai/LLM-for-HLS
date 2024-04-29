#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int index;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 1; i <= 8190; i++) {
    sol[i] = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j <= 8; j++) {
      index = i - 4 + j;
      if (index < 1 || 8192 < index) {
        continue;
      }
      sol[i] += filter[j] * orig[index];
    }
  }
//#pragma endscop
}
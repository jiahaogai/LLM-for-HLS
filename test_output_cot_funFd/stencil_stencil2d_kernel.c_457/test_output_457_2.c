orig;//input
sol;//output
filter;//filter
Error: 
Please check the code and try again.
#pragma ACCEL kernel
Error: 
Please check the code and try again.
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sol[i] = ((0 + filter[0]) * orig[i]) + ((0 + filter[1]) * orig[i + 32]) + ((0 + filter[2]) * orig[i + 64]) + ((0 + filter[3]) * orig[i + 96]) + ((0 + filter[4]) * orig[i + 128]) + ((0 + filter[5]) * orig[i + 160]) + ((0 + filter[6]) * orig[i + 192]) + ((0 + filter[7]) * orig[i + 224]) + ((0 + filter[8]) * orig[i + 256]) + ((0 + filter[9]) * orig[i + 288]);
  }
//#pragma endscop
}
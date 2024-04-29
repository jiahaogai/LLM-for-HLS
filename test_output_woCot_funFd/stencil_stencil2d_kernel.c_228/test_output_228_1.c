<<<<<<< HEAD
#pragma ACCEL kernel
=======
Code: #pragma ACCEL PIPELINE auto{off}
Error: #pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
int main( )
{
  int i;
  int j;
  int k;
  int result;
  int orig[8192];
  int sol[8192];
  int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_array(orig,8192);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  solver(orig,sol,filter,16,16,16);
  result = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 16; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 16; j++) {
      result += orig[i * 16 + j] - sol[i * 16 + j];
    }
  }
  printf("Result = %d\n",result);
  return 0;
}
#pragma ACCEL kernel
void init_array(int orig[8192],int init_val)
{
  int i;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8192; i++) {
    orig[i] = init_val;
  }
}
#pragma ACCEL kernel
void solver(int orig[8192],int sol[8192],int filter[9],int DP_FACTOR,int CHUNK_FACTOR,int MIN_CHUNK)
{
  int i;
  int j;
  int k;
  int result;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 16; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 16; j++) {
      result = ((0 + filter[0]) * orig[i * 16 + j]) + ((0 + filter[1]) * orig[i * 16 + ((j - 1) < 0 ? 0 : (j - 1))]) + ((0 + filter[2]) * orig[i * 16 + ((j + 1) > 15 ? 15 : (j + 1))]) + ((0 + filter[3]) * orig[i * 16 + ((j - 2) < 0 ? 0 : (j - 2))]) + ((0 + filter[4]) * orig[i * 16 + ((j + 2) > 15 ? 15 : (j + 2))]) + ((0 + filter[5]) * orig[i * 16 + ((j - 3) < 0 ? 0 : (j - 3))]) + ((0 + filter[6]) * orig[i * 16 + ((j + 3) > 15 ? 15 : (j + 3))]) + ((0 + filter[7]) * orig[i * 16 + ((j - 4
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

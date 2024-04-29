Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int buf;
  int index;
  int flatten_index_0;
  int flatten_index_1;
  int tmp_0;
  int tmp_1;
  int tmp_2;
  int tmp_3;
  int tmp_4;
  int tmp_5;
  int tmp_6;
  int tmp_7;
  int tmp_8;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_i:
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 337; j++) {
      flatten_index_0 = ((i - 1) * 337) + j;
      tmp_0 = orig[flatten_index_0 - 337] + orig[flatten_index_0 - 336] + orig[flatten_index_0 - 335] + orig[flatten_index_0 - 1] + orig[flatten_index_0 + 1] + orig[flatten_index_0 + 335] + orig[flatten_index_0 + 336] + orig[flatten_index_0 + 337] - 8 * orig[flatten_index_0];
      tmp_1 = orig[flatten_index_0 - (337 * 2)] + orig[flatten_index_0 - (337 * 1)] + orig[flatten_index_0 + (337 * 1)] + orig[flatten_index_0 + (337 * 2)] - 4 * orig[flatten_index_0];
      buf = tmp_1 + filter[0] * tmp_0;
      sol[flatten_index_0] = buf;
/* Standardize from: for(k = 1; k < 9; k++) {...} */
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
      for (k = 1; k < 9; k++) {
        flatten_index_1 = ((i - 1) * 337) + j - 1 + k;
        tmp_2 = orig[flatten_index_1 - 335] + orig[flatten_index_1 - 334] + orig[flatten_index_1 - 333] + orig[flatten_index_1 - 332] + orig[flatten_index_1 - 331] + orig[flatten_index_1 - 330] + orig[flatten_index_1 - 329] + orig[flatten_index_1 - 328] + orig[flatten_index_1 - 327] + orig[flatten_index_1 - 326] + orig[flatten_index_1 - 325] + orig[flatten_index_1 - 324] + orig[flatten_index_1 - 323] + orig[flatten_index_1 - 322] + orig[flatten_index_1 - 321] + orig[flatten_index_1 - 320] + orig[flatten_index_1 - 319] + orig[flatten_index_1 - 318] + orig[flatten_index_1 - 317] + orig[flatten_index_1 - 316] + orig[flatten_index_1 - 315] + orig[flatten_index_1 - 314] + orig[flatten_index_1 - 313] + orig[flatten_index_1 - 312] + orig
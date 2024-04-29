Code: ### Function Body:
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_up:
/* Standardize from: for(row = 1; row < 8191; row++) {...} */
  for (row = 1 + 8191 * 0; row < 1 + 8191 * 1; row += 8191 * 1) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_up_up:
/* Standardize from: for(col = 1; col < 8191; col++) {...} */
    for (col = 1 + 8191 * 0; col < 1 + 8191 * 1; col += 8191 * 1) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_t:
      for (k = 0; k < 9; ++k) {
        row_up = row - 1 + ((k - 4) * 8191);
        row_down = row + ((k - 4) * 8191);
        col_left = col - 1 + ((k - 4) * 1);
        col_right = col + ((k - 4) * 1);
        t += ((row_up < 1) ? 1 : ((row_up > 8191) ? 8191 : orig[row_up * 8192 + col_left]));
        t += ((row_down > 8191) ? 8191 : orig[row_down * 8192 + col_left]);
        t += ((col_left < 1) ? 1 : ((col_left > 8191) ? 8191 : orig[row_left * 8192 + col_left]));
        t += ((col_right > 8191) ? 8191 : orig[row_left * 8192 + col_right]);
      }
      sol[row * 8192 + col] = t;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### Function Body:
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### Function Body:
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: unknown type name ‘Function’; did you mean ‘union’?
    1 | ### Function Body:
      |     ^~~~~~~~
      |     union
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:18: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    1 | ### Function Body:
      |                  ^

Please check the code and try again.
Code: ### Function Body:
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int row_up;
  int row_down;
  int col;
  int col_left;
  int col_right
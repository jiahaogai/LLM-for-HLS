Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    result = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 9; k++) {
      result += filter[k] * orig[i + template_offsets[k].i] ;
    }
    sol[i] = result;
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - Define a parameter 'NUM_ITERATIONS' of type 'int' with a default value of 4.
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:22: warning: character constant too long for its type
    2 | - Define a parameter 'NUM_ITERATIONS' of type 'int' with a default value of 4.
      |                      ^~~~~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:47: warning: multi-character character constant [-Wmultichar]
    2 | - Define a parameter 'NUM_ITERATIONS' of type 'int' with a default value of 4.
      |                                               ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:8:22: warning: character constant too long for its type
    8 | - Define a parameter 'TILE_FACTOR' of type 'int' with a default value of  auto{126}.
      |                      ^~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:8:44: warning: multi-character character constant [-Wmultichar]
    8 | - Define a parameter 'TILE_FACTOR' of type 'int' with a default value of  auto{126}.
      |                                            ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:8:84: error: expected identifier or ‘(’ before ‘.’ token
    8 | - Define a parameter 'TILE_FACTOR' of type 'int' with a default value of  auto{126}.
      |                                                                                    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:11:22: warning: character constant too long for its type
   11 | - Define a parameter 'PIPELINE' of type 'int' with a default value of  auto{}.
      |                      ^~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:11:41: warning: multi-character character constant [-Wmultichar]
   11 | - Define a parameter 'PIPELINE' of type 'int' with a default value of  auto{}.
      |                                         ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:11:78: error: expected identifier or ‘(’ before ‘.’ token
   11 | - Define a parameter 'PIPELINE' of type 'int' with a default value of  auto{}.
      |                                                                              ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:14:22: warning: character constant too long for its type
   14 | - Define a parameter 'PARALLEL_FACTOR' of type 'int' with a default value of  auto{1}.
      |                      ^~~~~~~~~~~~~~~~~
/
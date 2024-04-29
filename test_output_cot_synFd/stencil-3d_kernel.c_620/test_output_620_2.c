Code: ### #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{4}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long NX;
  long NY;
  long NZ;
  long CONST;
  long hm;
  long hu;
  long hv;
  long hw;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_parms(C0,C1,&NX,&NY,&NZ,&CONST,&hm,&hu,&hv,&hw);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_i:
  for (i = 1; i < NX - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < NY - 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_k:
      for (k = 1; k < NZ - 1; k++) {
        idx = ((k * (NY - 2L)) + j) * (NX - 2L) + i;
        sol[idx] = CONST * (orig[idx] + hm * (sol[idx - 1L] + sol[idx + 1L]) + hu * (sol[idx - NX] + sol[idx + NX]) + hv * (sol[idx - NX - 1L] + sol[idx - NX + 1L] + sol[idx + NX - 1L] + sol[idx + NX + 1L]) + hw * (sol[idx - NX - NY] + sol[idx - NX + NY] + sol[idx + NX - NY] + sol[idx + NX + NY]));
      }
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:1: error: stray ‘##’ in program
    1 | ### #pragma ACCEL kernel
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:3: error: stray ‘#’ in program
    1 | ### #pragma ACCEL kernel
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:5: error: stray ‘#’ in program
    1 | ### #pragma ACCEL kernel
      |     ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:6: error: unknown type name ‘pragma’; did you mean ‘_Pragma’?
    1 | ### #pragma ACCEL kernel
      |      ^~~~~~
      |      _Pragma
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:19: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘kernel’
    1 | ### #pragma ACCEL kernel
      |                   ^~~~~~

Please check the code and try again.
Code: ### #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{4}

void stencil3d(long C0,
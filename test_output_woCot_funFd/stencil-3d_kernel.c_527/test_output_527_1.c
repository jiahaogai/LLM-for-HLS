<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}
=======
#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
<<<<<<< HEAD
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
  long sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k > 32L; k--) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j > 32L; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i > 32L; i--) {
        k_col = ((32L + 1L) * (32L + 1L)) * k;
        j_col = (32L + 1L) * j;
        i_col = i;
        sum = 0L;
        loopbuf:
        for (long _in_buf = 0; _in_buf < 27L; _in_buf++) {
          buf[_in_buf] = orig[((_in_buf + i_col) - 1L) + ((j_col + _in_buf) - 1L) + (k_col - 1L)];
          sum += buf[_in_buf];
        }
        sol[i_col + j_col + k_col] = sum;
      }
    }
  }
}
=======
  long i_col;
  long j_col;
  long k_col;
  long i_row;
  long j_row;
  long k_row;
  long bound;
  long t1;
  long t2;
  long t3;
  long t4;
  long t5;
  long t6;
  long t7;
  long t8;
  long t9;
  long t10;
  long t11;
  long t12;
  long t13;
  long t14;
  long t15;
  long t16;
  long t17;
  long t18;
  long t19;
  long t20;
  long t21;
  long t22;
  long t23;
  long t24;
  long t25;
  long t26;
  long t27;
  long t28;
  long t29;
  long t30;
  long t31;
  long t32;
  long t33;
  long t34;
  long t35;
  long t36;
  long t37;
  long t38;
  long t39;
  long t40;
  long t41;
  long t42;
  long t43;
  long t44;
  long t45;
  long t46;
  long t47;
  long t48;
  long t49;
  long t50;
  long t51;
  long t52;
  long t53;
  long t54;
  long t55;
  long t56;
  long t57;
  long t58;
  long t59;
  long t60;
  long t61;
  long t62;
  long t63;
  long t64;
  long t65;
  long t66;
  long t67;
  long t68;
  long t69;
  long t70;
  long t71;
  long t72;
  long t73;
  long t74;
  long t75;
  long t76;
  long t77;
  long t78;
  long t79;
  long t80;
  long t81;
  long t82;
  long t83;
  long t84;
  long t85;
  long t86;
  long t87;
  long t88;
  long t89;
  long t90;
  long t91;
  long t92;
  long t93;
  long t94;
  long t95;
  long t96;
  long t97;
  long t98;
  long t99;
  long t100;
  long t101;
  long t102;
  long t103;
  long t104;
  long t105;
  long t106;
  long t107;
  long t108;
  long t109;
  long t110;
  long t111;
  long t112;
  long t113;
  long t114;
  long t115;
  long t116;
  long t117;
  long t118;
  long t119;
  long t120;
  long t121;
  long t122;
  long t123;
  long t124;
  long t125;
  long t126;
  long t127;
  long t128;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

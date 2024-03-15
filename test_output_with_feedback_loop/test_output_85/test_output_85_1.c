7. Turn off automatic parallelization for the following loop.
8. Turn off automatic parallelization for the following loop.
9. Turn off automatic parallelization for the following loop.
10. Turn off automatic parallelization for the following loop.
11. Turn off automatic parallelization for the following loop.
12. Turn off automatic parallelization for the following loop.
13. Turn off automatic parallelization for the following loop.
14. Turn off automatic parallelization for the following loop.
15. Turn off automatic parallelization for the following loop.
16. Turn off automatic parallelization for the following loop.
17. Turn off automatic parallelization for the following loop.
18. Turn off automatic parallelization for the following loop.
19. Turn off automatic parallelization for the following loop.
20. Turn off automatic parallelization for the following loop.
21. Turn off automatic parallelization for the following loop.
22. Turn off automatic parallelization for the following loop.
23. Turn off automatic parallelization for the following loop.
24. Turn off automatic parallelization for the following loop.
25. Turn off automatic parallelization for the following loop.
26. Turn off automatic parallelization for the following loop.
27. Turn off automatic parallelization for the following loop.
28. Turn off automatic parallelization for the following loop.
29. Turn off automatic parallelization for the following loop.
30. Turn off automatic parallelization for the following loop.
31. Turn off automatic parallelization for the following loop.
32. Turn off automatic parallelization for the following loop.
33. Turn off automatic parallelization for the following loop.
34. Turn off automatic parallelization for the following loop.
35. Turn off automatic parallelization for the following loop.
36. Turn off automatic parallelization for the following loop.
37. Turn off automatic parallelization for the following loop.
38. Turn off automatic parallelization for the following loop.
39. Turn off automatic parallelization for the following loop.
40. Turn off automatic parallelization for the following loop.
41. Turn off automatic parallelization for the following loop.
42. Turn off automatic parallelization for the following loop.
43. Turn off automatic parallelization for the following loop.
44. Turn off automatic parallelization for the following loop.
45. Turn off automatic parallelization for the following loop.
46. Turn off automatic parallelization for the following loop.
47. Turn off automatic parallelization for the following loop.
48. Turn off automatic parallelization for the following loop.
49. Turn off automatic parallelization for the following loop.
50. Turn off automatic parallelization for the following loop.
51. Turn off automatic parallelization for the following loop.
52. Turn off automatic parallelization for the following loop.
53. Turn off automatic parallelization for the following loop.
54. Turn off automatic parallelization for the following loop.
55. Turn off automatic parallelization for the following loop.
56. Turn off automatic parallelization for the following loop.
57. Turn off automatic parallelization for the following loop.
58. Turn off automatic parallelization for the following loop.
59. Turn off automatic parallelization for the following loop.
60. Turn off automatic parallelization for the following loop.
61. Turn off automatic parallelization for the following loop.
62. Turn off automatic parallelization for the following loop.
63. Turn off automatic parallelization for the following loop.
64. Turn off automatic parallelization for the following loop.
65. Turn off automatic parallelization for the following loop.
66. Turn off automatic parallelization for the following loop.
67. Turn off automatic parallelization for the following loop.
68. Turn off automatic parallelization for the following loop.
69. Turn off automatic parallelization for the following loop.
70. Turn off automatic parallelization for the following loop.
71. Turn off automatic parallelization for the following loop.
72. Turn off automatic parallelization for the following loop.
73. Turn off automatic parallelization for the following loop.
74. Turn off automatic parallelization for the following loop.
75. Turn off automatic parallelization for the following loop.
76. Turn off automatic parallelization for the following loop.
77. Turn off automatic parallelization for the following loop.
78. Turn off automatic parallelization for the following loop.
79. Turn off automatic parallelization for the following loop.
80. Turn off automatic parallelization for the following loop.
81. Turn off automatic parallelization for the following loop.
82. Turn off automatic parallelization for the following loop.
83. Turn off automatic parallelization for the following loop.
84. Turn off automatic parallelization for the following loop.
85. Turn off automatic parallelization for the following loop.
86. Turn off automatic parallelization for the following loop.
87. Turn off automatic parallelization for the following loop.
88. Turn off automatic parallelization for the following loop.
89. Turn off automatic parallelization for the following loop.
90. Turn off automatic parallelization for the following loop.
91. Turn off automatic parallelization for the following loop.
92. Turn off automatic parallelization for the following loop.
93. Turn off automatic parallelization for the following loop.
94. Turn off automatic parallelization for the following loop.
95. Turn off automatic parallelization for the following loop.
96. Turn off automatic parallelization for the following loop.
97. Turn off automatic parallelization for the following loop.
98. Turn off automatic parallelization for the following loop.
99. Turn off automatic parallelization for the following loop.
100. Turn off automatic parallelization for the following loop.
 #pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{30}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{12}
    for (i = 1; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 0; j < 240; j++) {
        ey[i][j] = ey[i][j] - 0.5 * (hz[i][j] - hz[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 0; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (j = 1; j < 240; j++) {
        ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (j = 0; j < 240 - 1; j++) {
        int i_col = -1 * i;
        int j_row = -1 * j;
        hz[i][j] = hz[i][j] - 0.7 * (ex[i_col + 1][j_row + 1] - ex[i][j_row + 1] - ey[i_col + 1][j][j_row + 1] + ey[i][j][j_row + 1]);
      }
    }
  }
}
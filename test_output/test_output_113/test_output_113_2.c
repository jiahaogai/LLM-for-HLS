
7. Turn off automatic loop blocking for the following loop.
8. Use the original, full form of the loop without breaking it into smaller chunks.
9. Run the iterations of the loop with a parallel factor of 16.
10. Run the iterations of the first inner loop with a parallel factor of 2.
11. Run the iterations of the second inner loop with a parallel factor of 2.
12. Turn off automatic loop blocking for the following loop.
13. Use the original, full form of the loop without breaking it into smaller chunks.
14. Run the iterations of the loop with a parallel factor of 1.
15. Run the iterations of the first inner loop with a parallel factor of 2.
16. Run the iterations of the second inner loop with a parallel factor of 2.
17. Turn off automatic loop blocking for the following loop.
18. Use the original, full form of the loop without breaking it into smaller chunks.
19. Run the iterations of the loop with a parallel factor of 1.
20. Run the iterations of the first inner loop with a parallel factor of 1.
21. Run the iterations of the second inner loop with a parallel factor of 1.
22. Turn off automatic loop blocking for the following loop.
23. Use the original, full form of the loop without breaking it into smaller chunks.
24. Run the iterations of the loop with a parallel factor of 1.
25. Run the iterations of the first inner loop with a parallel factor of 2.
26. Run the iterations of the second inner loop with a parallel factor of 2.
27. Turn off automatic loop blocking for the following loop.
28. Use the original, full form of the loop without breaking it into smaller chunks.
29. Run the iterations of the loop with a parallel factor of 1.
30. Run the iterations of the first inner loop with a parallel factor of 1.
31. Run the iterations of the second inner loop with a parallel factor of 1.
32. Turn off automatic loop blocking for the following loop.
33. Use the original, full form of the loop without breaking it into smaller chunks.
34. Run the iterations of the loop with a parallel factor of 1.
35. Run the iterations of the first inner loop with a parallel factor of 1.
36. Run the iterations of the second inner loop with a parallel factor of 1.
37. Turn off automatic loop blocking for the following loop.
38. Use the original, full form of the loop without breaking it into smaller chunks.
39. Run the iterations of the loop with a parallel factor of 1.
40. Run the iterations of the first inner loop with a parallel factor of 1.
41. Run the iterations of the second inner loop with a parallel factor of 1.
42. Turn off automatic loop blocking for the following loop.
43. Use the original, full form of the loop without breaking it into smaller chunks.
44. Run the iterations of the loop with a parallel factor of 1.
45. Run the iterations of the first inner loop with a parallel factor of 1.
46. Run the iterations of the second inner loop with a parallel factor of 1.
47. Turn off automatic loop blocking for the following loop.
48. Use the original, full form of the loop without breaking it into smaller chunks.
49. Run the iterations of the loop with a parallel factor of 1.
50. Run the iterations of the first inner loop with a parallel factor of 1.
51. Run the iterations of the second inner loop with a parallel factor of 1.
52. Turn off automatic loop blocking for the following loop.
53. Use the original, full form of the loop without breaking it into smaller chunks.
54. Run the iterations of the loop with a parallel factor of 1.
55. Run the iterations of the first inner loop with a parallel factor of 1.
56. Run the iterations of the second inner loop with a parallel factor of 1.
57. Turn off automatic loop blocking for the following loop.
58. Use the original, full form of the loop without breaking it into smaller chunks.
59. Run the iterations of the loop with a parallel factor of 1.
60. Run the iterations of the first inner loop with a parallel factor of 1.
61. Run the iterations of the second inner loop with a parallel factor of 1.
62. Turn off automatic loop blocking for the following loop.
63. Use the original, full form of the loop without breaking it into smaller chunks.
64. Run the iterations of the loop with a parallel factor of 1.
65. Run the iterations of the first inner loop with a parallel factor of 1.
66. Run the iterations of the second inner loop with a parallel factor of 1.
67. Turn off automatic loop blocking for the following loop.
68. Use the original, full form of the loop without breaking it into smaller chunks.
69. Run the iterations of the loop with a parallel factor of 1.
70. Run the iterations of the first inner loop with a parallel factor of 1.
71. Run the iterations of the second inner loop with a parallel factor of 1.
72. Turn off automatic loop blocking for the following loop.
73. Use the original, full form of the loop without breaking it into smaller chunks.
74. Run the iterations of the loop with a parallel factor of 1.
75. Run the iterations of the first inner loop with a parallel factor of 1.
76. Run the iterations of the second inner loop with a parallel factor of 1.
77. Turn off automatic loop blocking for the following loop.
78. Use the original, full form of the loop without breaking it into smaller chunks.
79. Run the iterations of the loop with a parallel factor of 1.
80. Run the iterations of the first inner loop with a parallel factor of 1.
81. Run the iterations of the second inner loop with a parallel factor of 1.
82. Turn off automatic loop blocking for the following loop.
83. Use the original, full form of the loop without breaking it into smaller chunks.
84. Run the iterations of the loop with a parallel factor of 1.
85. Run the iterations of the first inner loop with a parallel factor of 1.
86. Run the iterations of the second inner loop with a parallel factor of 1.
87. Turn off automatic loop blocking for the following loop.
88. Use the original, full form of the loop without breaking it into smaller chunks.
89. Run the iterations of the loop with a parallel factor of 1.
90. Run the iterations of the first inner loop with a parallel factor of 1.
91. Run the iterations of the second inner loop with a parallel factor of 1.
92. Turn off automatic loop blocking for the following loop.
93. Use the original, full form of the loop without breaking it into smaller chunks.
94. Run the iterations of the loop with a parallel factor of 1.
95. Run the iterations of the first inner loop with a parallel factor of 1.
96. Run the iterations of the second inner loop with a parallel factor of 1.
97. Turn off automatic loop blocking for the following loop.
98. Use the original, full form of the loop without breaking it into smaller chunks.
99. Run the iterations of the loop with a parallel factor of 1.
100. Run the iterations of the first inner loop with a parallel factor of 1.
101. Run the iterations of the second inner loop with a parallel factor of 1.

 #pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[60][80],double ey[60][80],double hz[60][80],double _fict_[40])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{3}
    for (j = 0; j < 80; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL
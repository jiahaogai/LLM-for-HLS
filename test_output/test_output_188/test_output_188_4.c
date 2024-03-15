

	.file	"optimize_loop.c"
	.section .mdebug.abi32
	.previous
	.text
	.align 2
	.p2align 4,,15
	.global optimize_loop
	.type	optimize_loop, @function
optimize_loop:
.LFB34:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$168, %esp
	leal	160(%ebp), %eax
	movl	%eax, 120(%esp)
	leal	156(%ebp), %eax
	movl	%eax, 116(%esp)
	leal	152(%ebp), %eax
	movl	%eax, 112(%esp)
	leal	148(%ebp), %eax
	movl	%eax, 108(%esp)
	leal	144(%ebp), %eax
	movl	%eax, 104(%esp)
	leal	140(%ebp), %eax
	movl	%eax, 100(%esp)
	leal	136(%ebp), %eax
	movl	%eax, 96(%esp)
	leal	132(%ebp), %eax
	movl	%eax, 92(%esp)
	leal	128(%ebp), %eax
	movl	%eax, 88(%esp)
	leal	124(%ebp), %eax
	movl	%eax, 84(%esp)
	leal	120(%ebp), %eax
	movl	%eax, 80(%esp)
	leal	116(%ebp), %eax
	movl	%eax, 76(%esp)
	leal	112(%ebp), %eax
	movl	%eax, 72(%esp)
	leal	108(%ebp), %eax
	movl	%eax, 68(%esp)
	leal	104(%ebp), %eax
	movl	%eax, 64(%esp)
	leal	100(%ebp), %eax
	movl	%eax, 60(%esp)
	leal	96(%ebp), %eax
	movl	%eax, 56(%esp)
	leal	92(%ebp), %eax
	movl	%eax, 52(%esp)
	leal	88(%ebp), %eax
	movl	%eax, 48(%esp)
	leal	84(%ebp), %eax
	movl	%eax, 44(%esp)
	leal	80(%ebp), %eax
	movl	%eax, 40(%esp)
	leal	76(%ebp), %eax
	movl	%eax, 36(%esp)
	leal	72(%ebp), %eax
	movl	%eax, 32(%esp)
	leal	68(%ebp), %eax
	movl	%eax, 28(%esp)
	leal	64(%ebp), %eax
	movl	%eax, 24(%esp)
	leal	60(%ebp), %eax
	movl	%eax, 20(%esp)
	leal	56(%ebp), %eax
	movl	%eax, 16(%esp)
	leal	52(%ebp), %eax
	movl	%eax, 12(%esp)
	leal	48(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	44(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	40(%ebp), %eax
	movl	%eax, (%esp)
	call	bbgemm
	movl	120(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	116(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	112(%ebp), %eax
	movl	%eax, (%esp)
	call	bbgemm
	movl	108(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	104(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	100(%ebp), %eax
	movl	%eax, (%esp)
	call	bbgemm
	movl	96(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	92(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	88(%ebp), %eax
	movl	%eax, (%esp)
	call	bbgemm
	movl	84(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	80(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	76(%ebp), %eax
	movl	%eax, (%esp)
	call	bbgemm
	movl	72(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	68(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	64(%ebp), %eax
	movl	%eax, (%esp)
	call	bbgemm
	movl	60(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	56(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	52(%ebp), %eax
	movl	%eax, (%esp)
	call	bbgemm
	movl	48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	44(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	40(%ebp), %eax
	movl	%eax, (%esp)
	call	bbgemm
	movl	36(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	32(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	28(%ebp), %eax
	movl	%eax, (%esp)
	call	bbgemm
	movl	24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	bbgemm
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	4(%ebp), %eax
	movl	%eax, (%esp)
	call	bbgemm
	movl	4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%eax, (%esp)
	call	bcopy
	movl	4(%ebp), %e
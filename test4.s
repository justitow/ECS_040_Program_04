	.file	"test4.c"
	.text
	.align 2
.globl main
	.type	main,@function
main:
.LFB2:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	subl	$88, %esp
.LCFI2:
	andl	$-16, %esp
	movl	$0, %eax
	subl	%eax, %esp
	movl	$197, -12(%ebp)
	cmpl	$99, -12(%ebp)
	jg	.L2
	movl	$134, -16(%ebp)
	jmp	.L3
.L2:
	movl	$26, -16(%ebp)
.L3:
	movl	$0, -76(%ebp)
.L4:
	cmpl	$2, -76(%ebp)
	jle	.L7
	jmp	.L5
.L7:
	movl	-76(%ebp), %edx
	movl	-16(%ebp), %eax
	addl	-12(%ebp), %eax
	movl	%eax, -72(%ebp,%edx,4)
	leal	-76(%ebp), %eax
	incl	(%eax)
	jmp	.L4
.L5:
	movl	-52(%ebp), %eax
	addl	$18, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	leave
	ret
.LFE2:
.Lfe1:
	.size	main,.Lfe1-main
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.2.3 20030502 (Red Hat Linux 3.2.3-49)"

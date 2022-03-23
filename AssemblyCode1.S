 // ARM Cortex Assembly program that takes the average and standard deviation of 8 floating point numbers
 
 
 
 .data
 	.type a, %object
 	.type n, %object
 	.size a, 8
 	.size n, 1
n:  .float 8

a:
    .float 17.3, 12.15, 3.32, 7.37, 31.4, 27.5, 5.6, 19.7

    .text
 	.global main
 	.global average
 	.global deviation
 	.global swap
 	.arch armv8-a+fp+simd
 	.type main, %function
 	.type average, %function
 	.type deviation, %function

 	average:
 		SUB X5, X5, X5 // temp X1 = 0
 		LSL X5, X5, #2 // i*4
 		ADD X5, X5, X1 // X1 + X5 = X5
 		SUB X4, X4, X4 // i = 0
 		FSUB S3, S3, S3 // float sum = 0.0

 		LDUR S4,[X5, #0] // load a[i]
 		ADD X5, X5, #4 // shift iterator to next element
 		FADD S3, S3, S4 // sum + a[i]
 		ADD X4, X4, #1 // i++
 		CMP X4, X3 // i < n
 		B.LT sum
 	sum1:
 		SCVTF S9, X4 // convert i to float
 		FDIV S1, S3 ,S9 // sum/n
 		BR X30 // return

 	deviation:
 		SUB X5, X5, X5 //temp X1 = 0
 		LSL X5, X5, #2 // i*4
 		ADD X5, X5, X1 // X5 = X1 + X5
 		SUB X4, X4, X4 // i = 0
 		FSUB S3, S3, S3 // float sum = 0.0

 		LDUR S4,[X5, #0] // load a[i]
 		ADD X5, X5, #4 // shift 4 bits
 		FADD S3, S3, S4 // sum = sum + a[i]
 		ADD X4, X4, #1 // i++
 		CMP X4, X3 // i < n
 		B.LT sum2

 	sum2:
 		SCVTF S9, X4 // converts to float
 		FDIV S1, S3, S9 // sum/n
 		FSUB S6, S4, S1 // S6 = a[i]-avg
 		FMUL S7, S6, S6 // S7 = (a[i]-avg)^2
 		FADD S3, S3, S7 // sum = sum + (a[i]-avg)^2
 		FDIV S8, S3, S9 // S8 = sum/n
 		FSQRT S2, S8 // sqrt(sum/n)
 		BR X30

 		main:
 			ADRP X0, a //load the array address a to X0
 			ADD X0, X0, :lo12:a
 			ADRP X1, n // load address of n to X1
 			ADD X1, X1, :lo12:n

 			LDUR S10,[X1, #0]
 			LDUR X2, [X0, #0]

 			BL average
 			BL deviation

 		exit:


 	// ARM Cortex assembly program that indicates largest and smallest values in a set
  
  .data
 	.type a, %object
 	.type n, %object
 	.size n, 1
 	.size a, 10
n:  .xword 10
a:
  	.xword 79,55,94,48,19,13,45,2,3,99 // 64-bit values



 	.text
 	.global main
 	.global find_smallest
 	.global find_largest
 	.global swap
 	.arch armv8-a+fp+simd
 	.type find_smallest, %function
 	.type find_largest, %function
 	.type swap, %function
 	.type   main, %function

    find_largest:
    	LSL X10, X1, #3   //i*8
    	ADD X10, X10, X0  //a[i] address
    	LDUR X3,[X10,#0]  //value of largest
    	MOV X4,X1         //index of largest
    loop1:
    	LDUR X9,[X10,#0] //next a[i]
    	CMP X9, X3       //check for new largest value
    	B.LE skip1
    	MOV X3,X9        // new largest
    	MOV X4,X1        // new index
    skip1:
    	ADD X1,X1, #1 // i++
    	ADD X10, X10, #8 //address of a[i]
    	CMP X1, X2 //check for loop is done
    	B.LT loop1
    	BR X30 // return

    find_smallest:
    	LSL X10, X1, #3 // i*8
    	ADD X10, X10, X0 // a[i] address
    	LDUR X3, [X10, #0]
    	MOV X4, X1
    loop2:
    	LDUR X9, [X10, #0]
    	CMP X9, X3  // check for new smallest value
    	B.LE skip2
    	MOV X3, X9 // new smallest
    	MOV X4,X1 // new index
    skip2:
    	ADD X1, X1, #1 // i++
    	ADD X10, X10, #8
    	CMP X1, X2
    	B.GT loop2
    	BR X30 // return

    swap:
    	LSL X10, X1, #3 // i*8
    	ADD X10, X10, X0 // address of a[i]
    	LSL X12, X2, #3 // j*8
    	ADD X12, X12, X0 // address of a[j]
    	STUR X5,[X10, #0] // store a[j] into a[i]
    	STUR X4, [X12, #0] // store a[i] into a[j]
    	BR X30 // return

    main:
    	ADRP X0, a
    	ADD X0, X0, lo12:a
    	ADRP X2, n // address of a
    	ADD X2, X2, :lo12:n
    	LDUR X2, [X2, #0] // load n
    	SUB X1, X1, X1  // initialize i=0
   loopmain:
   	CMP X1, X2 //check i<n
   	B.GE exit
   	BL find_smallest // calls smallest function
   	BL swap // calls swap function
   	BL find_largest // calls largest function
   	BL swap // calls swap function
   	ADD X1, X1, #1 // i = i+1
   	SUB X2, X2, #1 // n = n-1
   	B loopmain




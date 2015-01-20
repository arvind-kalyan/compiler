t2 dw 0
a dw 0
t4 dw 0
t5 dw 0
t6 dw 0
b dw 0
g dw 0
h dw 0
u dw 0
c dw 0
t11 dw 0
sum dw 0
t13 dw 0
diff dw 0
t1 dw 0
t3 dw 0
t7 dw 0
z dw 0
t9 dw 0
t10 dw 0
t12 dw 0
t14 dw 0
t0 dw 0
x dw 0
mov AX, mat1
mov BX,[
mov AX,BX
mov mat1,AX
mov AX, s
mov BX,"abcd"
mov AX,BX
mov s,AX
mov AX, 2
mov BX,5
add AX,BX
mov CX,AX
mov t2,CX
mov AX, a
mov BX,t2
mov AX,BX
mov a,AX
mov AX, a
mov BX,4
sub AX,BX
mov CX,AX
mov t4,CX
mov AX, 3
mov BX,1
sub AX,BX
mov CX,AX
mov t5,CX
mov AX, t4
mov BX,t5
imul BX
mov CX,AX
mov t6,CX
mov AX, b
mov BX,t6
mov AX,BX
mov b,AX
mov AX, g
mov BX,10
mov AX,BX
mov g,AX
mov AX, h
mov BX,9
mov AX,BX
mov h,AX
mov AX, u
mov BX,12
mov AX,BX
mov u,AX
mov AX, c
mov BX,b
add AX,BX
mov CX,AX
mov t11,CX
mov AX, sum
mov BX,t11
mov AX,BX
mov sum,AX
mov AX, c
mov BX,a
sub AX,BX
mov CX,AX
mov t13,CX
mov AX, diff
mov BX,t13
mov AX,BX
mov diff,AX
mov AX, function
mov BX,function
mov AX,BX
mov function,AX
mov AX, a
mov BX,g
sub AX,BX
mov CX,AX
mov t1,CX
mov AX, h
mov BX,u
add AX,BX
mov CX,AX
mov t2,CX
mov AX, t1
mov BX,t2
imul BX
mov CX,AX
mov t3,CX
mov AX, 13
mov BX,a
sub AX,BX
mov CX,AX
mov t4,CX
mov AX, u
mov BX,g
add AX,BX
mov CX,AX
mov t5,CX
mov AX, t4
mov BX,t5
imul BX
mov CX,AX
mov t6,CX
mov AX, t3
mov BX,t6
add AX,BX
mov CX,AX
mov t7,CX
mov AX, z
mov BX,t7
mov AX,BX
mov z,AX
mov AX, a
mov BX,g
sub AX,BX
mov CX,AX
mov t9,CX
mov AX, h
mov BX,u
add AX,BX
mov CX,AX
mov t10,CX
mov AX, t9
mov BX,t10
imul BX
mov CX,AX
mov t11,CX
mov AX, 10
mov BX,a
add AX,BX
mov CX,AX
mov t12,CX
mov AX, u
mov BX,g
add AX,BX
mov CX,AX
mov t13,CX
mov AX, t12
mov BX,t13
imul BX
mov CX,AX
mov t14,CX
mov AX, t11
mov BX,t14
sub AX,BX
mov CX,AX
mov t0,CX
mov AX, g
mov BX,t0
mov AX,BX
mov g,AX
mov ax,g
mov bx,2
cmp ax,bx
jne L32
mov AX, x
mov BX,5
mov AX,BX
mov x,AX
jmp L33
L32: 
mov AX, x
mov BX,10
mov AX,BX
mov x,AX
L33: 
mov ax,g
mov bx,2
cmp ax,bx
jnl L35
mov AX, x
mov BX,15
mov AX,BX
mov x,AX
jmp L36
L35: 
mov AX, x
mov BX,20
mov AX,BX
mov x,AX
L36: 
ret

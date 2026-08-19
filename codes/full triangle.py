def triangle(n):
    num=1
    for i in range(n):
        for j in range(n-i-1):
            print(" ",end="")
            
        for j in range(2*i+1):
            print(i,end=" ")
            num +=1
            
        print()
            
   
t=int(input("enter number of patterns: "))
for i in range(t):
    n=int(input(f"num of row/col for pattern {i+1}:"))
    triangle(n)
    print()                       
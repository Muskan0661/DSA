def printing(n):
    num=1
    for i in range(1,n+1):
        for j in range(i,n+1):
            
            print(num,end=" ")
            num+=1
        print()    
     
t=int(input("enter number of patterns: "))
for i in range(t):
    n=int(input(f"num of row/col for pattern {i+1}:"))
    printing(n)
    print()            
    
    
    
    
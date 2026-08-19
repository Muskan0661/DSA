def pattern(n):
    for i in range(n):
        for j in range(n):
            print("*",end=" ")
        
        print()    

t=int(input("enter num types:"))
for i in range(t):
    n=int(input(f"enter num of rows/col of pattern {i+1} : "))

    pattern(n) 
    print()
    
            
            
            
x = 1
while (x > 0): 
    x = int(input("x: "))
    if x <= 0:
        break
    n = 2*x
    m = 3*x
    n1 = x
    m1 = 2*x-1
    print("n: "+str(n+n1))
    print("m: "+str(m+m1))
    print("n+m: "+str(n+m+n1+m1))
    with open('customtest.txt','w') as f:
        f.write(str(n+n1)+" "+str(m+m1)+'\n')
        for y in range(0,x):
            f.write(str(2*y)+" "+str(2*y+1)+'\n')
            f.write(str(2*y+1)+" "+str(2*y+2)+'\n')
            f.write(str(2*y)+" "+str(2*y+2)+'\n')
        for y in range(n,n+x):
            f.write(str(y)+" "+str(n+x)+'\n')
        for y in range(n,n+x):
            f.write(str(y)+" "+str(y+1)+'\n')

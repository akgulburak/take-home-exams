
def ifintercept(x,y):
	intercept=[]
	x.append(x[0])
	y.append(y[0])

	epsilon=0.001
	for i in range(len(x)-1):
		xnotzero=x[i+1][0]-x[i][0]
		if abs(xnotzero) > epsilon:	
			m1=(x[i+1][1]-x[i][1])/(x[i+1][0]-x[i][0])
		for j in range(len(y)-1):
			ynotzero=y[j+1][0]-y[j][0]
			if abs(ynotzero) > epsilon:
				m2=(y[j+1][1]-y[j][1])/(y[j+1][0]-y[j][0])
			if abs(ynotzero)>epsilon or abs(xnotzero)>epsilon:
				if abs(ynotzero)>epsilon and abs(xnotzero)> epsilon:
					if  abs(m1)>epsilon and abs(m2)>epsilon:
						if  abs(ynotzero)>epsilon and abs(xnotzero)>epsilon and abs(m1-m2)>epsilon :
							d = (m1*x[i][0]-x[i][1]-m2*y[j][0]+y[j][1])/(m1-m2)        		
							root=m1*(d-x[i][0])+x[i][1]
							bool2=d-x[i][0]>epsilon and d-x[i+1][0]<epsilon
							bool3=d-x[i][0]<epsilon and d-x[i+1][0]>epsilon
							bool4=d-y[j][0]>epsilon and d-y[j+1][0]<epsilon
							bool5=d-y[j][0]<epsilon and d-y[j+1][0]>epsilon
							bool6=bool2 or bool3
							bool7=bool4 or bool5
							bool1=bool6 and bool7
							if bool1:
								intercept.append((d,root))
				if abs(ynotzero)>epsilon:
					if abs(xnotzero)<epsilon and abs(m2)>epsilon:
						decide1=m2*(x[i][0]-y[j][0])+y[j][1]
						decide2=decide1-x[i+1][1]<epsilon and decide1-x[i][1]>epsilon
						decide3=decide1-x[i][1]<epsilon and decide1-x[i+1][1]>epsilon
						decide4=decide2 or decide3
						decide5=y[j][0]-x[i][0]>epsilon and y[j+1][0]-x[i][0]<epsilon 
						decide6=y[j][0]-x[i][0]<epsilon and y[j+1][0]-x[i][0]>epsilon 
						decide7=decide5 or decide6
						if decide7 and decide4:
							intercept.append((x[i][0],decide1))
				if abs(xnotzero)>epsilon:
					if abs(ynotzero)<epsilon and abs(m1)>epsilon:
						decide8=m1*(y[j][0]-x[i][0])+x[i][1]
						decide9=decide8-y[j+1][1]<epsilon and decide8-y[j][1]>	epsilon
						decide10=decide8-y[j][1]<epsilon and decide8-y[j+1][1]>epsilon
						decide11=decide9 or decide10
						decide12=y[j][0]-x[i+1][0]>epsilon and y[j][0]-x[i][0]<epsilon 
						decide13=y[j][0]-x[i][0]<epsilon and y[j][0]-x[i+1][0]>epsilon 
						decide14=decide12 or decide13
					
						if decide11 and decide14:
							intercept.append((y[j][0],decide8))
				
				if abs(xnotzero)>epsilon and abs(ynotzero)>epsilon:
					if abs(m1)<epsilon and abs(m2)>epsilon:
						d = (-x[i][1]-m2*y[j][0]+y[j][1])/(-m2)
						boolm1=x[i+1][0]-d<epsilon and x[i][0]-d>epsilon
						boolm2=x[i][0]-d<epsilon and x[i+1][0]-d>epsilon
						boolm3=boolm1 or boolm2
						boolm4=x[i][1]-y[j][1]<epsilon and x[i][1]-y[j+1][1]>epsilon
						boolm5=x[i][1]-y[j+1][1]<epsilon and x[i][1]-y[j][1]>epsilon
						boolm6=boolm4 or boolm5
						boolm7=boolm3 and boolm6
						if boolm7:
							intercept.append((d,x[i+1][1]))
					if abs(m2)<epsilon and abs(m1)>epsilon:
						d = (m1*x[i][0]-x[i][1]+y[j][1])/(m1)
						boolm8=y[j][0]-d<epsilon and y[j+1][0]-d>epsilon
						boolm9=y[j+1][0]-d<epsilon and y[j][0]-d>epsilon
						boolm10=boolm8 or boolm9
						boolm11=y[j][1]-x[i][1]<epsilon and y[j][1]-x[i+1][1]>epsilon
						boolm12=y[j][1]-x[i+1][1]<epsilon and y[j][1]-x[i][1]>epsilon
						boolm13=boolm11 or boolm12
						boolm14=boolm10 and boolm13
						
						if boolm14:
							intercept.append((d,y[j+1][1]))
			if abs(xnotzero)>epsilon:
				if abs(ynotzero)<epsilon and abs(m1)<epsilon:
					y_1=x[i][1]
					x_1=y[j][0]
					bools1=x[i][0]-y[j][0]<epsilon and x[i+1][0]-y[j][0]>epsilon
					bools2=x[i+1][0]-y[j][0]<epsilon and x[i][0]-y[j][0]>epsilon
					bools3=bools1 or bools2
					bools4=x[i][1]-y[j][1]<epsilon and x[i+1][1]-y[j+1][1]>epsilon
					bools5=x[i][1]-y[j+1][1]<epsilon and x[i+1][1]-y[j][1]>epsilon
					bools6=bools4 or bools5
					if bools3 and bools6:
						intercept.append((x_1,y_1))
			if abs(ynotzero)>epsilon:
				if abs(xnotzero)<epsilon and abs(m2)<epsilon :
					y_2=y[j][1]
					x_2=x[i][0]
					bools_1=y[j][0]-x[i][0]<epsilon and y[j+1][0]-x[i][0]>epsilon
					bools_2=y[j+1][0]-x[i][0]<epsilon and y[j][0]-x[i][0]>epsilon
					bools_3=bools_1 or bools_2
					bools_4=y[j][1]-x[i][1]<epsilon and y[j][1]-x[i+1][1]>epsilon
					bools_5=y[j][1]-x[i+1][1]<epsilon and y[j][1]-x[i][1]>epsilon
					bools_6=bools_4 or bools_5
					if bools_3 and bools_6:
						intercept.append((x_2,y_2))
				
	return intercept




def ifin(x,y):
	
	intercept=[]
	epsilon=0.001
	if len(x)==4:
		x2=[x[2],x[0],x[1]]
	if len(x)==5:
		x2=[x[2],x[3],x[0],x[1],x[2]]
	boolone=True
	for j in range(len(y)-1):
		b1=y[j][0]
		b2=y[j][1]
		boold=True
		for i in range(len(x)-1):
			xnotzero=x[i+1][0]-x[i][0]
			if abs(xnotzero)>epsilon :
				m1=(x[i+1][1]-x[i][1])/(x[i+1][0]-x[i][0])
				if abs(m1)>epsilon:
			
					m1=(x[i+1][1]-x[i][1])/(x[i+1][0]-x[i][0])
					lineb1=m1*(b1-x[i][0])+x[i][1]-b2
					line1=m1*(x2[i][0]-x[i][0])+x[i][1]-x2[i][1]
					if len(x)==5:
						line2=m1*(x2[i+1][0]-x[i][0])+x[i][1]-x2[i+1][1]
						if line2>epsilon:
							line2=1
						else:
							line2=-1
					if line1>epsilon:
						line1=1
					else:
						line1=-1
					if lineb1>epsilon:
						lineb1=1
					else:
						lineb1=-1
				if abs(m1)<epsilon:
					if x2[i][1]-x[i][1]>epsilon:
						line1="ust"
					if x2[i][1]-x[i][1]<epsilon:
						line1="alt"
					if len(x)==5:
						if x2[i+1][1]-x[i][1]>epsilon:
							line2="ust"
						if x2[i+1][1]-x[i][1]<epsilon:
							line2="alt"
						
					if b2-x[i][1]>epsilon:
						lineb1="ust"
					if b2-x[i][1]<epsilon:
						lineb1="alt"
			if abs(xnotzero)<epsilon:

				if x2[i][0]-x[i][0]>epsilon:
					line1="sag"
				if x2[i][0]-x[i][0]<epsilon:
					line1="sol"
				if len(x)==5:
					if x2[i+1][0]-x[i][0]>epsilon:
						line2="sag"
					if x2[i+1][0]-x[i][0]<epsilon:
						line2="sol"
				if b1-x[i][0]>epsilon:
					lineb1="sag"
				if b1-x[i][0]<epsilon:
					lineb1="sol"
			if lineb1!=line1:
				boold=False
			if len(x)==5 and boolone:
				if line1!=line2:
					boold=False
					boolone=False
					concbegin=x2[i+1]
					if i==0:
						z=[x[3],x[0],x[1],x[3]]
						t=[x[3],x[2],x[1],x[3]]
						return ifin(z,y)+ifin(t,y)
						
					elif i==1:
						z=[x[2],x[0],x[1],x[2]]
						t=[x[3],x[2],x[0],x[3]]
						return ifin(z,y)+ifin(t,y)
						
					elif i==2:
						z=[x[3],x[2],x[1],x[3]]
						t=[x[3],x[0],x[1],x[3]]
						return ifin(z,y)+ifin(t,y)
						
					elif i==3:
						z=[x[0],x[1],x[2],x[0]]
						t=[x[3],x[2],x[0],x[3]]
						return ifin(z,y)+ifin(t,y)
						
		if 	boold:
			intercept.append([b1,b2])
	return intercept

def minority_shape_intersect(a1,b1):
	
	output= ifintercept(a1,b1)+ifin(a1,b1)+ifin(b1,a1)
	if len(output)<=2:
		return []
	else:
		return output

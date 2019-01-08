
def check_if_true(solution,Corpus,i,gridsize):

#row vs row
	for k in range(i):

		if solution[k]==solution[k+1]:
			return False

#check if list is complete 

	if i==gridsize-1: 


#column vs column
		
		x=0
		y=0

		while x<gridsize-1:
			y=x+1

			while y<gridsize:
				bool2=True
				for z in range(gridsize):
					if solution[x][z]!=solution[y][z]:
						bool2=False
				y+=1
				if bool2:
					return False	
			x+=1	

		"""
		solution[0][0]=solution[0][0]	
		solution[0][1]=solution[1][0]
		solution[0][2]=solution[2][0]
		solution[0][gridsize]=solution[gridsize][0]

		solution[0][0]==solution[0][1]
		solution[0][1]==solution[1][1]
		solution[0][gridsize]==solution[gridsize][1]


		solution[0][0]==solution[0][gridsize]
		solution[0][gridsize]==solution[gridsize][gridsize]	


		solution[1][0]=solution[0][0]	
		solution[1][1]=solution[1][0]
		solution[1][2]=solution[2][0]
		solution[1][gridsize]=solution[gridsize][0]

		solution[1][0]==solution[0][1]
		solution[1][1]==solution[1][1]
		solution[1][gridsize]==solution[gridsize][1]


		solution[1][0]==solution[0][gridsize]
		solution[1][gridsize]==solution[gridsize][gridsize]	

		solution[gridsize][0]==solution[0][0]
		"""

		p=0

		while p<gridsize: #row vs column
		
			j=0	

			while j<gridsize:
				bool3=True
				for l in range(gridsize):
					if solution[p][l]!=solution[l][j]:
						bool3= False
				j+=1
				if bool3:
					return False
			p+=1		

#to control if columns is in Corpus

	for q in range(gridsize):
		
		bool1=False
		
		for w in range(len(Corpus)):

			boolx=True
			if solution[0][q]==Corpus[w][0]:
				
				for e in range(1,i+1):
		
					if solution[e][q]!=Corpus[w][e]:
						boolx=False
				if boolx:
					bool1=True
					break
		if not bool1:
			return False
		"""
		solution[0][0]==Corpus[0][0]
		solution[0][0]==Corpus[1][0]
		solution[0][0]==Corpus[2][0]
			solution[1][0]==Corpus[2][1]
			solution[2][0]==Corpus[2][2]
			solution[3][0]==Corpus[2][3]
			solution[i][0]==Corpus[2][i]
		solution[0][0]==Corpus[3][0]
			solution[1][0]==Corpus[3][1]
			solution[2][0]==Corpus[3][2]
			solution[3][0]==Corpus[3][3]
			solution[i][0]==Corpus[3][i]
		solution[0][0]==Corpus[len(Corpus)][0]



		solution[0][1]==Corpus[0][0]
		solution[0][1]==Corpus[1][0]
		solution[0][1]==Corpus[2][0]
			solution[1][1]==Corpus[2][1]
			solution[2][1]==Corpus[2][2]
			solution[3][1]==Corpus[2][3]
			solution[i][1]==Corpus[2][i]
		solution[0][1]==Corpus[3][0]
			solution[1][1]==Corpus[3][1]
			solution[2][1]==Corpus[3][2]
			solution[3][1]==Corpus[3][3]
			solution[i][1]==Corpus[3][i]
		solution[0][1]==Corpus[len(Corpus)][0]



		solution[0][gridsize]==Corpus[0][0]
	

		


		solution[0][0] == Corpus[0][0]
		solution[1][0] == Corpus[1][0]
		solution[2][0] == Corpus[len(Corpus)][0]
		
		solution[0][1] == Corpus[0][]
		solution[1][1] == Corpus[1][]
		solution[2][1] == Corpus[len(Corpus)][]
		
		solution[0][2] == Corpus[0][]
		solution[1][2] == Corpus[1][]
		solution[2][gridsize] == Corpus[len(Corpus)][]
		
		solution[0][0] == Corpus[0][]
		solution[1][0] == Corpus[1][]
		solution[2][0] == Corpus[len(Corpus)][]
		
		solution[1] == Corpus[0]
		solution[1] == Corpus[1]
		solution[1] == Corpus[len(Corpus)]	
		


		solution[0][0] == Corpus[0][0]
		solution[0][0] == Corpus[1][0]
		solution[0][0] == Corpus[2][0]
		solution[0][0] == Corpus[3][0]
		solution[0][0] == Corpus[len(Corpus)][0]
		
		solution[][]
		"""
	return True		

		


def placing(i,Corpus,gridsize,solution):

	if i<gridsize:
		n = 0

		while n<len(Corpus):

			solution[i]=Corpus[n]
			
			if check_if_true(solution,Corpus,i,gridsize): 
				
				
				if placing(i+1,Corpus,gridsize,solution):
					return True			
				
				else:

					if n+1<len(Corpus):
						n+=1
						solution[i]=Corpus[n]
				
					else:
						return False

				"""
					if n+1<len(Corpus)-1:

						i+=1
						n+=1
					
					else:

						return solution
				
				"""
				
			else:
				
				if n+1<len(Corpus):
					n+=1
				
				else:
					"""
					if i>0:
					
						i-=1
						n=0


						# n=Corpus.index(solution[i])
					
						if n+1<len(Corpus)-1:
							solution[i]=Corpus(n+1)
							i+=1
							n=0
						else:
							i-=1
					"""

					return False
					"""
					else:
						return False
					"""

	else:
		return solution


def place_words(Corpus):
	i=0
	gridsize=len(Corpus[0])
	solution=[["0"*gridsize]]*gridsize

	placing(i,Corpus,gridsize,solution)
	if solution[0]!=solution[1]:
		return solution
	else:
		return False

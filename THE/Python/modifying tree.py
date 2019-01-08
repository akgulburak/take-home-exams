def is_leaf(tree):
	return len(tree)==2
def nofchild(tree):
	return len(tree)-2
def children(tree):
	return tree[2:]
def datum(tree):
	return tree[:2]

flattened=[]	

def flattener(liste):
	if is_leaf(liste): 
		flattened.append(datum(liste))
		return flattened

	flattened.append(datum(liste))

	for i in range(nofchild(liste)): #traversing childrens
		flattener(children(liste)[i])

	return flattened

def sub_childs(liste):
	sublist=[]
	for i in range(nofchild(liste)):
		sublist.extend(flattener(children(liste)[i]))
		global flattened #that was the mistake I couldnt see before
		flattened=[]
	return sublist

stack=[]

def all_sub_childs(liste,a): 
	a+=1
	for i in children(liste):	

		stack.append([datum(i),a])
		all_sub_childs(i,a)
#def all_sub_childs(liste): 
#	all_sublist= sub_childs(liste)
#	
#
#	for i in (children(liste)):
#		print i
#	for j in (children(liste)):
#		all_sub_childs(j)
#	return all_sublist
stack_r=[0]

def correctionizer(liste):
	if liste==[]:
		return []
	if liste[0][-1]=="/":
		liste[0]=liste[0][:-1]

	for i in children(liste):
		correctionizer(i)
	

def swap_reverse(liste,a,f,m):
	m=stack_r[-1]
	if datum(liste)==a:
		if True:
			liste[:2]=f[:]

		m+=1
		stack_r.append(m) 

	for i in (children(liste)):
	
		swap_reverse(i,a,f,m)


def swap(liste,ts,tbs): 
	if datum(liste)==ts:
		liste[:2]=tbs[0]+"/",tbs[1]
	

	all_sublist= sub_childs(liste)

	for i in (children(liste)):
		swap(i,ts,tbs)


def compare_max(liste,stack):
	max_len=0
	for i in stack:
		if i[1]>max_len:
			max_len=i[1]

	max_element=[[0,0],0]
	for j in range(1,max_len):
		for z in stack:
			if z[1]==j:
				for k in stack:
					if z[1]<k[1]:
						if z[0][1]<k[0][1] and k[0][1]>max_element[0][1]:
							max_element=k 
				if max_element!=[[0,0],0]:
					stack.remove(max_element)
					stack.remove(z)
					swap(liste,z[0],max_element[0])
					m=0

					swap_reverse(liste,max_element[0],z[0],m)
					
				max_element=[[0,0],0]

def constraint_1(liste):
	all_sub_childs(liste,0) # stack i kullanacaksin cunku stackde var ne gerekiyorsa
	compare_max(liste,stack)	
	correctionizer(liste)
					
	return liste

def max_len_finder(liste):
	all_sub_childs(liste,0)

	max_len=0
	for i in stack:
		if i[1]>max_len:
			max_len=i[1]

	return max_len

final_stack=[]
def final_all_sub_childs(liste,a): 
	a+=1
	for i in children(liste):	

		final_stack.append([datum(i),a])
		final_all_sub_childs(i,a)


def parent_finder(liste,child):
	if liste == []:
		return []
	return [[child]+liste[0]] + parent_finder(liste[1:],child)

def path_finder(liste):
	if is_leaf(liste):
		return [[datum(liste)]]
	path_list=[]
	for i in children(liste):
		path_list.extend(parent_finder(path_finder(i),datum(liste)))

	return path_list



def check(liste,node):
	global stack
	stack=[]
	all_sub_childs(liste,0)
	for i in stack:
		for k in stack:
			if i[1]<k[1] and i[0][1]<k[0][1]: # means violates constraint_1
				return False
	sum_of_children=0
	for j in children(node):
		sum_of_children+=j[1]
	
	if node!=[]:	
		if sum_of_children>node[1]:
			return False # means violates constaint_2

	return True

def f_traverse(liste):
	for i in children(liste):
		f_traverse(i)

def insert_it(bigtree,tree,liste,insert,swapped):
	
	if datum(tree)==liste:
		tree.append(insert[0])
		swapped[0]=True
		if not check(bigtree,tree):
			tree.remove(insert[0])
			swapped[0]=False
#	if is_leaf(tree): I dont know whether it gives error
#		return []
	for i in children(tree):
		insert_it(bigtree,i,liste,insert,swapped)		

def insertion(tree,liste,T,eliminated_ones):
	swapped=[False]
	for i in range(T):
		if not swapped[0]:
			insert_it(tree,tree,liste[0][i],liste[-1],swapped)
	if swapped[0]:
		eliminated_ones.pop()

#	for t in children(liste): silme islemi ilk yaptirilacak
#		if t==tbi:
#			liste.remove(tbi)


#	for j in parents:
#		print 
#		remove_threshold(liste,tbi[0])
#		remove_empty(liste)
#		insertion(liste,j,tbi[0])

#def remove_duplicate(liste):
#
#	for i in range(len(liste)-1):
#		for j in range(1,len(liste)):
#			if liste[i] == liste[j]:
#				del liste[i]

def removal(liste,thlevel):

	if datum(liste)==thlevel[0]:
		del liste[2:]
		return
	for i in children(liste):

		removal(i,thlevel)

def constraint_2(liste,T):
#i deleted max_len_finder here
	final_all_sub_childs(liste,0) # final_stack kullan
	list_of_threshold=[]

	for i in final_stack:
		if i[1]>=T+1: 
			paths=path_finder(liste)
			for j in paths:
				for l in j:
					if i[0]==l:
						location=j.index(i[0])
						path_found=j[:location]
						tbi=i
						list_of_threshold.append([path_found,tbi])
	maxnumber=0

	for t in list_of_threshold:
	
		if t[1][1]>maxnumber:
			maxnumber=t[1][1]
	
	last_elements=[]

	for y in range(T+1,maxnumber+1):
		for k in list_of_threshold:
			if k[-1][1]==y:
				last_elements.append(k)

	tidy_list=[] # tidy_list is the list that will be used to do all of the changes so IT IS IMPORTANT!!!
# and it is also contains the paths and elements below the given threshold
#I will use this list's element's last element to decide whether i should send it to removal or not
#Here it is what I will send to removal process which will begin before insertion to not make a mistake
#Let given threshold T,then T[CORRECTION] will go to removal process and no more
#All the items which includes T+1 and the others will be sent to insertion process but I think sending the bottom ones first
#is a bit more safe but I'm not 100% sure so I may do it randomly at first

	for g in last_elements:
		bool1=True
		for x in tidy_list:
			if g==x:
				bool1=False
		if bool1:
			tidy_list.append(g) #contains all the items needed for transfer
#But I really need the items on the threshold level


	for f in final_stack:
		if f[-1]==T:
			removal(liste,f)
#use the reformed T for finding the index which of items will inserted in the tidy_list 
	
	eliminated_ones=[]

	for q in tidy_list:
		global eliminated_ones
		eliminated_ones.append(q[-1][0][0])

		insertion(liste,q,T,eliminated_ones)


def help_ben_solo(liste,T):
	
	constraint_1(liste)
	maxi=max_len_finder(liste)
	correctionizer(liste)
	constraint_2(liste,maxi-T+1)

	return (liste,eliminated_ones)

#stack[0] stack[1],2,3,4,5...
#stack[1] stack[2],3,4.....
# sub_childs(hehe)
# sub_childs(children(hehe)[0])
# sub_childs(children(hehe)[1])
# sub_childs(children(children(hehe)[0])[0])
# sub_childs(children(children(hehe)[0])[1])
# sub_childs(children(children(hehe)[0])[2])
# sub_childs(children(children(hehe)[1])[0])
# sub_childs(children(children(hehe)[1])[1])
#
#

#print sub_childs(children(children(hehe)[0])[2])	

#print flattener(hehe)
#flattened=[] important!!!
#print flattener(children(hehe)[0])
#flattened=[] important!!!
#print flattener(children(hehe)[1])


#BULMAK iciN KULLAN(FiNDiNG ALGORiTHM)
"""
def all_sub_childs(liste): 
	all_sublist= sub_childs(liste)

	for i in (children(liste)):
		print i
		all_sub_childs(i)
"""

#def all_sub_childs(liste): 
#	all_sublist= sub_childs(liste)
#islem
#islem
#	for i in (children(liste)):
##		print i
#		all_sub_childs(i)


"""
def compare(liste,stack):

	if stack==[]:
		return []
	
	for j in range(1,len(stack)):
		if stack[0][1]<stack[j][1]:
			if stack[0][0][1]<stack[j][0][1]:
				swap(liste,stack[0][0],stack[j][0])
	return compare(liste,stack[1:])
"""

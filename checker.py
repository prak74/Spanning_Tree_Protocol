import os
os.system('g++ -o bsim main.cpp bridgesim.cpp bridge.cpp')
input_directory = r'testcases'
output_directory = r'outputs'
for filename in os.listdir(input_directory):
		x = os.path.splitext(filename)[0]
		if "inp" in x : 
			y = x.replace("inp","out",1)
			os.system('bsim < testcases\\{} > outputs\\{}.txt'.format(x, y))

for filename in os.listdir(output_directory):
		x = os.path.splitext(filename)[0]
		if "out" in x:
			print("{}: Checking".format(filename))
			os.system("FC /W testcases\\{} outputs\\{}.txt".format(x, x))

# os.system('rm myoutputs/*')
os.system('rm bsim')
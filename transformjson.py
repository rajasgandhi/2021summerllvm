import json

infile = open('output.json','r')
outfile = open('outputtransformed.json','w')

text = infile.read().splitlines()

object_string = ""
x = 0
while x < len(text):
    if "function_body" not in text[x]:
        object_string += text[x] + "\n"
    if "function_body" in text[x]:
        y = x
        temparray = []
        while "calls_functions" not in text[y]:
            temparray.append(text[y])
            y += 1
            if "calls_functions" not in text[x+1]:
                x += 1  
        object_string += r'\n'.join([str(z) for z in temparray]) + "\n"
    x += 1

object_string = object_string.replace(object_string[-6:], "}\n]")
outfile.write(object_string)

infile.close()
outfile.close()

#with open('outputtransformed.json') as f:
    #data = json.load(f)
    #for function in data:
        #print(function)
        #for k, calls in data[function].items():
            #list1 = k
            #print(list1)
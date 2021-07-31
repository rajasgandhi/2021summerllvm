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

f = open('outputtransformed.json')
data = json.load(f)
f.close()

for function in data:
    for fName, fInfo in function.items():
        updateList = list(set(fInfo["calls_functions"]))
        fInfo["calls_functions"] = updateList

f = open('outputtransformed.json', 'w+')
f.write(json.dumps(data, indent=4))
f.close()
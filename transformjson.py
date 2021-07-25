import re

infile = open('output.json','r')
outfile = open('outputtransformed.json','w')

'''text = ""
for each in infile:
    text += each

matches = re.finditer("\"body\"", text)
matches_positions = [match.start() for match in matches]
#print(matches_positions)'''

lines = infile.readlines()
for line in lines:
    if(line.startswith("\t\"body")):
        print(True)

#newcontents = text.replace(text[-6:], "}\n}")
#outfile.write(newcontents)

infile.close()
outfile.close()
'''with open('output.json') as f:
    data = json.load(f)
print(data)'''

infile = open('output.json','r')
outfile = open('outputtransformed.json','w')
text = ""
for each in infile:
    text += each
newcontents = text.replace(text[-6:], "}\n}")
outfile.write(newcontents)
infile.close()
outfile.close()
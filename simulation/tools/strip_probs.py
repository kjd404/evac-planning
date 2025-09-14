f = open( "topologyTestProbSet", "r" )
firstline = f.readline()
lines = []
nine = 10
ten = 11
counter = 0
prebuilt = '2 0.500000 0.500000\n'
for line in f:
    if line != firstline:
        if counter % 21 == nine or counter % 21 == ten:
            lines.append( prebuilt )
        else:
            lines.append( line )
    if counter == 21:
        counter = 0
    else:
        counter = counter + 1
f.close()
f = open( "topologyTestProbSetEdit", "w" )
f.write( firstline )
for line in lines:
    f.write( line )
f.close()

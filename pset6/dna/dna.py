from sys import argv
import csv

strDict = {
    "AGATC" : 0,
    "AATG" : 0,
    "TATC" : 0
}

if len(argv) == 3:
    # argv[1] : csv
    # argv[2] : sequence

    # Open csv and text file (csv reader and DictReader) (sys.argv command line arg)
    cvsReader = csv.DictReader(open(argv[1], "r"))
    """
    for row in cvsReader:
        print(row['name'], row['AGATC'], row['AATG'], row['TATC'])
    """

    # text file open(file) f.read()
    f = open(argv[2], "r")
    seq = f.read()

    strA = 0
    strB = 0
    strC = 0
    # compute longest run for each STR len(s) s[i:j]
    for i in range(len(seq)):
        if seq[i:i+5] == "AGATC":
            temp = 0
            while seq[i:i+5] == "AGATC":
                temp += 1
                i += 5
            if temp > strA:
                strA = temp

    """
    - Compute STR repeates for each position
    - Keep checking substrings while repeat
    """
    for i in range(len(seq)):
        if seq[i:i+4] == "AATG":
            temp = 0
            while seq[i:i+4] == "AATG":
                temp += 1
                i += 4
            if temp > strB:
                strB = temp

    for i in range(len(seq)):
        if seq[i:i+4] == "TATC":
            temp = 0
            while seq[i:i+4] == "TATC":
                temp += 1
                i += 4
            if temp > strC:
                strC = temp

    # compare counts to csv file
    """
    Store in data structure (dictionary)
    *dont check first row*
    """
    found = False
    for row in cvsReader:
        if(int(row['AGATC']) == strA and int(row['AATG']) == strB and int(row['TATC']) == strC):
            print(row['name'])
            found = True
    if found == False:
        print("No match")
else:
    print("Usage: python dna.py data.csv sequence.txt")

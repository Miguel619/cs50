from sys import argv
import csv

def main():
    if len(argv) == 3:
        # argv[1] : csv containing peoples dna info
        # argv[2] : sequence of dna we are testing for

        # Open csv and text file (csv reader and DictReader) (sys.argv command line arg)
        cvsReader = csv.DictReader(open(argv[1], "r"))

        # text file open(file) f.read()
        f = open(argv[2], "r")
        seq = f.read()

        # compute longest run for each STR len(s) s[i:j]
        """
        - Compute STR repeates for each position
        - Keep checking substrings while repeat
        """
        strA = computeSTR(seq, 5, "AGATC")
        strB = computeSTR(seq, 4, "AATG")
        strC = computeSTR(seq, 4, "TATC")
        if argv[1] == "databases/large.csv":
            strD = computeSTR(seq, 8, "TTTTTTCT")
            strE = computeSTR(seq, 5, "TCTAG")
            strF = computeSTR(seq, 4, "GATA")
            strG = computeSTR(seq, 4, "GAAA")
            strH = computeSTR(seq, 4, "TCTG")

        # compare counts to csv file
        """
        Store in data structure (dictionary)
        *dont check first row*
        """
        found = False
        for row in cvsReader:
            if argv[1] == "databases/large.csv":
                if(int(row['AGATC']) == strA and int(row['AATG']) == strB and int(row['TATC']) == strC and int(row['TTTTTTCT']) == strD and int(row['TCTAG']) == strE and int(row['GATA']) == strF and int(row['GAAA']) == strG and int(row['TCTG']) == strH):
                    print(row['name'])
                    found = True
            elif argv[1] == "databases/small.csv":
                if(int(row['AGATC']) == strA and int(row['AATG']) == strB and int(row['TATC']) == strC):
                    print(row['name'])
                    found = True
        if found == False:
            print("No match")
    else:
        print("Usage: python dna.py data.csv sequence.txt")

def computeSTR(seq, n, case):
    max = 0
    for i in range(len(seq)):
            if seq[i:i+n] == case:
                temp = 0
                while seq[i:i+n] == case:
                    temp += 1
                    i += n
                if temp > max:
                    max = temp
    return max

main()
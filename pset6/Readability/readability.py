def main():
    text = input("text: ")
    letters = 0
    sentance = 0
    words = 0
    end = False
    # count letters words and sentances
    for i in text:
        # increment letters if i is a letter 
        if ord(i.lower()) > 96 and ord(i.lower()) < 123:
            letters += 1
        # increment letters and sentances if we encount . ? !
        elif ord(i) == 33 or ord(i) == 46 or ord(i) == 63:
            words += 1
            sentance += 1
            # lets also skip the next whitespace
            end = True
            continue
        elif ord(i) == 32 and end == False:
            words += 1
        end = False
    # Coleman-Liau index to compute readability 0.0588 * L - 0.296 * S - 15.8
    # L = letters per 100 words     S = sentences per 100 words
    grade = round(0.0588 * ((letters/words)*100) - 0.296 * ((sentance/words)*100) - 15.8)
    # print result
    if grade >= 16:
        print("Grade: 16+")
    if grade <= 0:
        print("Before Grade: 1")
    else:
        print("Grade: ", grade)

main()
import re

amex = "^[3][4|7]\d{13}$"

mc = "^[5][1|2|3|4|5]\d{14}$"

visa = "^[4](\d{12}|\d{15})$"


num = input("Number: ")

if(re.search(amex, num)):
    print("AMEX")
elif(re.search(mc, num)):
    print("MASTERCARD")
elif(re.search(visa, num)):
    print("VISA")
else:
    print("INVALID")
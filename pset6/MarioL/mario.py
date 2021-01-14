
# Declare size for while loop
height = 0
# initialize spaces to 1
spaces = 1
# while input between 1 and 8
while (height <= 0 or height > 8):
    #take in input and cast to int
    height = input("Height: ")
    #if it fails to cast, set to 0
    try:
        height = int(height)
    except ValueError:
        height = 0
# for every line
for x in range(height):
    # print every space which is the hieght - spaces 
    print(" " * (height-spaces), end="")
    # print the # which = spaces
    print("#" * spaces, end="")
    # print the new line
    print()
    # next level of triangle
    spaces += 1
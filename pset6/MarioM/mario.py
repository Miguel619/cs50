height = 0
spaces = 1
# check input is an integer between 1 and 8
while(height < 1 or height> 8):
    height = input("Height: ")
    try:
        height = int(height)
    except ValueError:
        height = 0

# for every row
for i in range(height):
    # print spaces before
    print(" " * (height-spaces), end="")
    # print first triangle
    print("#" * spaces, end="")
    # print space between
    print("  ", end="")
    # print secong triangle
    print("#" * spaces, end="")
    #p go to next line
    print()
    # prep next row
    spaces += 1

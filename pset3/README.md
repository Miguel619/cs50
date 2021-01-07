# Problem Set 3:
From Harvard CS50 [Open CourseWare](https://cs50.harvard.edu/x/2021/)


| Assignment                   |    Status     |     Language    |
| ---------------------------- | ------------- | --------------- |
| [Plurality](https://cs50.harvard.edu/x/2021/psets/3/plurality/)                | Done         |         C       | 
| [Runoff](https://cs50.harvard.edu/x/2021/psets/3/runoff/)                | Done         |         C       |         
| [Tideman](https://cs50.harvard.edu/x/2021/psets/3/tideman/)                | Done         |         C       |



### Link From [Harvard](https://cs50.harvard.edu/college/2020/fall/psets/)

## [Plurality](https://cs50.harvard.edu/x/2021/psets/3/plurality/)
An election program that takes the candidates in the command line then prompts the user for the number of votes.  Finally the user votes and the winner is printed.
```
$ ./plurality Alice Bob Charlie
Number of voters: 4
Vote: Alice
Vote: Bob
Vote: Charlie
Vote: Alice
Alice
```
## [Runoff](https://cs50.harvard.edu/x/2021/psets/3/runoff/)
An election programs that only declares a winner if they recieve more than half the votes
If no one recieves more than half the votes the person with the least votes is eliminated and their vote goes to the candidate who was second preference.
If all candidates get the same amount of votes, the election is declared a tie.
```
./runoff Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Alice
```
## [Tideman](https://cs50.harvard.edu/x/2021/psets/3/tideman/)
This is a more complicated ranked pairs election.
```
./tideman Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Charlie
```


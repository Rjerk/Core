x = int(raw_input("Input a number: "))
epsilon = 0.01
guess = x / 2.0
numGuesses = 0
while abs(guess*guess - x) >= epsilon:
    guess = guess - ((guess**2) - x) / (2 * guess)
    numGuesses += 1

print "Square root of ", x, " is about ", guess
print "numGuesses = ", numGuesses

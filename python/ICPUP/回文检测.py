def isPalindrome(s):
    """s is s string.
    If s is Palindrome return True or return False
    Ignore sign, space"""

    def toChars(s):
        s = s.lower()
        letters = ""
        for c in letters:
            if c in "abcdefghijklmnopqrstuvwxyz":
                letters = letters + c
        return letters

    def isPal(s):
        if len(s) <= 1:
            return True
        else:
            return s[0] == s[-1] and isPal(s[1:-1])

    return isPal(toChars(s))

s = "DogGod"
print isPalindrome(s)

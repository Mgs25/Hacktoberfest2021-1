def stringReverse(s, c = 0):
    if c == len(s):
        return None
    stringReverse(s, c + 1)
    print(s[c], end = '')

stringReverse("Methran")

s = 'anagram'
t = 'ngaram'
dic_s = {}
dic_t = {}
def count(s, dic):
    for i in s:
        num = s.count(i)
        dic[i] = num

for i in dic_s:
    if dic_s[i] != dic_t[i]:
        return False

for j in dic_t:
    if dic_s[j] != dic_t[j]:
        return False



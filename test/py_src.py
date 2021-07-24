f = open('files.txt', 'r')

text = f.read()

files = text.split("\n")

res = ["\"${fileDirName}" + i[1:] + "\"" for i in files]

s = ""
len = len(res)
i = 0
for elem in res:
    if (i == len - 1):
        s += elem
    else:
        s += elem + ", "
    i += 1

print(s)
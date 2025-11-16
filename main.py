# AoA Project 3
# Vivian Tran & Cesar Diab


# Function to load the dictionary
def loadDictionary(fileName: str):
    words = set()
    with open(fileName, 'r') as f:
        for line in f:
            word = line.strip()
            if word:
                words.add(word)
    return words


# DP Function
def splitString(s, dictionary):
    n = len(s)
    INF = n+1

    # DP[i] holds the minimum number of dictionary words that it would take to split the input string
    dp = [INF] * (n+1)
    nextIdx = [-1] * (n+1)

    # Base case: no suffix, so that's 0 words
    dp[n] = 0
    nextIdx[n] = -1

    # DP
    for i in range(n-1, -1, -1):
        best = INF
        bestJ = -1

        for j in range(i+1, n+1):
            candidate = s[i:j]
            if candidate in dictionary and dp[j] != INF:
                cost = 1 + dp[j]
                if cost < best:
                    best = cost
                    bestJ = j
        dp[i] = best
        nextIdx[i] = bestJ

    # if dp[0] is inf we have no valid splitting
    if dp[0] == INF:
        return None
    
    # reconstruct split
    result = []
    i = 0
    while i < n:
        j = nextIdx[i]
        if j == -1:
            return None
        result.append(s[i:j])
        i = j
    return result

def main():
    fileName = "aliceInWonderlandDictionary.txt"
    inputPath = "input.txt"
    dictionary = loadDictionary(fileName)

    # Go through the input
    with open(inputPath, "r") as f:
        for line in f:
            s = line.strip()
            if not s:
                continue
            splitWords = splitString(s, dictionary)
            if splitWords is None:
                print(str(s) + " cannot be split into AiW words.")
            else:
                k = len(splitWords)
                wordsStr = " ".join(splitWords)
                print(str(s) + " can be split into "+ str(k) + " AiW words: " + str(wordsStr))

if __name__ == "__main__":
    main()
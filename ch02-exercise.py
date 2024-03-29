def addition_chain(N):
    chains = [[] for i in range(N+1)] # chains[i] 는 i를 최소의 addition횟수로 구할 수 있는 chain들의 리스트이다.
    chains[1] = [[1]]
    for i, r in enumerate(chains):
        level = N # INF
        # 가능한 chains[i]들 중에서 가장 짧은 chain의 길이를 구한다.
        for j in range(i//2, 0, -1): # i-j > j
            for sub in chains[i-j]:
                if j in sub:
                    level = min(len(sub), level)
        # 최소 길이의 chain들을 chains[i]에 추가한다.
        for j in range(i//2, 0, -1):
            for sub in chains[i-j]:
                if len(sub) == level and j in sub:
                    chains[i].append(sub +[i])
    return chains


def main():
    n = int(input("input chain limit(1~150): "))
    if n < 0 or n > 150:
        return -1
    chains = addition_chain(n)
    args = " "
    while args != "":
        args = input(f"input number(1~{n}): ")
        print(f"addition: {len(chains[int(args)][0])-1} chain: {chains[int(args)][0]}", end="\n\n")

if __name__ == "__main__":
    main()
    

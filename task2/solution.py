def main() -> None:
    with open("input1.txt") as file:
        file.readline() # skip useless N
        cables = set(
            tuple(int(x) for x in line.split()) for line in file
        )

    vertexes = set(x for x in cables for x in x[:-1])
    conn = {min(vertexes)}
    span = set()
    # Prim's algorhitm
    while len(conn) < len(vertexes):
        mins = set()
        for c in conn:
            for v in cables:
                if (v[0] == c or v[1] == c) and\
                (v[0] not in conn or v[1] not in conn):
                    mins.add(v)
        cable = min(mins, key=lambda x: x[2])
        conn.add(cable[0])
        conn.add(cable[1])
        span.add(cable)

    with open("output1.txt", "w") as file:
        sum_len = 0
        for n1, n2, d in cables-span:
            file.write(f"{n1} {n2}\n")
            sum_len += d
        file.write(str(sum_len))


if __name__ == "__main__":
    main()
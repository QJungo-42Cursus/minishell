

""" This will open the make file, read and find the objects, and return a list of strings of the objects paths. """
def get_makefile_objs() -> list[str]:
    makefile = open("Makefile", "r")
    makefile_lines = makefile.readlines()
    makefile.close()
    objs = []

    we_are_in: bool = False
    for line in makefile_lines:
        if line.startswith("SRCS"):
            we_are_in = True
        if we_are_in:
            if line.startswith("OBJS"):
                break
            else:
                objs.append(line)
    return objs

def main():
    print("Hello, world!");
    print(get_makefile_objs())






if __name__ == '__main__':
    main()

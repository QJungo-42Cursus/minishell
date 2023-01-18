

""" This will open the make file, read and find the objects, and return a list of strings of the objects paths. """
def get_makefile_srcs() -> list[str]:
    makefile = open("Makefile", "r")
    makefile_lines = makefile.readlines()
    makefile.close()
    srcs = []

    we_are_in: bool = False
    for line in makefile_lines:
        if line.startswith("SRCS"):
            we_are_in = True
        if we_are_in:
            if line.startswith("OBJS"):
                break
            else:
                new_line = line.replace('\t', '').replace('\n', '').replace(' ', '').replace('\\', '').replace('SRCS=', '')
                if new_line != '':
                    srcs.append(new_line)
    return srcs

""" This will return a list of strings of the functions in the file. """
def get_fonctions_from_file(file_path: str) -> list[str]:
    file = open(file_path, "r")
    file_lines = file.readlines()
    file.close()
    fonctions = []
    for line in file_lines:
        if not line.startswith("\t") and not line.startswith("{") and not line.startswith("}") and not line.startswith("#") and not line.startswith(" "):
            print(line)
    return fonctions

def main():
    srcs = get_makefile_srcs()
    for src in srcs:
        get_fonctions_from_file(src)

if __name__ == '__main__':
    main()

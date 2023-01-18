

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
                srcs.append(line.replace('\t', '').replace('\n', '').replace(' ', '').replace('\\', '').replace('SRCS=', ''))
    return srcs

""" This will return a list of strings of the functions in the file. """
def get_fonctions_from_file(file_path: str) -> list[str]:
    file = open(file_path, "r")
    file_lines = file.readlines()
    file.close()
    fonctions = []
    for line in file_lines:
        if line.startswith("void"):
            fonctions.append(line.replace("void", "").replace("(", "").replace(")", "").replace(" ", "").replace("\n", ""))
    return fonctions

def main():
    srcs = get_makefile_srcs()
    for obj in srcs:
        get_makefile_srcs(obj)
        print(obj)






if __name__ == '__main__':
    main()

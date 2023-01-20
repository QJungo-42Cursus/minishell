from dataclasses import dataclass, field
from typing import List

@dataclass()
class CFile:
    filename: str
    directory: str
    functions: list[str]

    def __repr__(self):
        return f"CFile (\n directory: {self.directory},\n filename: {self.filename},\n functions: {self.functions} \n)"

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
def get_functions_from_file(file_path: str) -> CFile:
    filename: str = file_path.split("/").pop()
    directory: str = file_path.split("/")[0]
    directory = '' if filename == directory else directory
    cfile = CFile(filename, directory, [])

    file = open(file_path, "r")
    file_lines = file.readlines()
    file.close()
    for line in file_lines:
        if line[0].isalpha() and not line.startswith("static"):
            cfile.functions.append(line.replace('\n', '').replace('\t', ' '))
    return cfile 

def main():
    srcs = get_makefile_srcs()
    cfiles = [get_functions_from_file(src) for src in srcs]
    buffer: str = ''
    current_directory: str = 'c'


    for cfile in cfiles:
        if not cfile.directory == current_directory:
            current_directory = cfile.directory
            buffer += f"\n{current_directory}/\n\n"
        buffer += f"\t{cfile.filename}\n"
        
        for func in cfile.functions:
            p1 = func.split(' ')[0]
            p2 = func.split(' ')[1:]
            buffer += f"\t|-\t\t\t{p1}\t{p2}\n"

    print(buffer)


if __name__ == '__main__':
    main()

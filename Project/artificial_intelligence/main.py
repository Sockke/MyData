import os 

i = 0


def show_all_file_path(dirname):
    for name in os.listdir(dirname):
        path = os.path.join(dirname, name)
        if os.path.isfile(path):
            print(path)
        else:
            show_all_file_path(path)


def show_file_tree(filename):
    global i
    i += 1
    line = i * "-"
    if os.path.isdir(filename):
        for name in os.listdir(filename):
            print(line + name)
            path = os.path.join(filename, name)
            show_file_tree(path)
            i -= 1

# show_all_file_path("./test")
show_file_tree("./test")
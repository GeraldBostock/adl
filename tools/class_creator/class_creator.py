from tkinter import *
from tkinter.filedialog import askdirectory

import re
import ctypes

kernel32 = ctypes.WinDLL('kernel32')
user32 = ctypes.WinDLL('user32')

SW_HIDE = 0

hWnd = kernel32.GetConsoleWindow()
if hWnd:
    user32.ShowWindow(hWnd, SW_HIDE)

def browse(Textbox):
    foldername=askdirectory()
    Textbox.insert(END, foldername)

def create_class_files(class_name, folder_path):

    if class_name == '' or folder_path == '':
        pass

    header_name = class_name + '.h'
    header_path = folder_path + '/' + header_name

    cpp_name = class_name + '.cpp'
    cpp_path = folder_path + '/' + cpp_name

    write_to_header_file(class_name, header_path)
    write_to_cpp_file(class_name, cpp_path)

def write_to_header_file(class_name, file_path):
    f = open(file_path, "w+")
    header_guard = ''

    words = re.findall('[A-Z][^A-Z]*', class_name)
    print(words)

    if class_name.startswith('adl'):
        header_guard += 'adl_'

    i = 0
    while i < len(words):
        header_guard += words[i].lower()
        i += 1

    header_guard += '_h__'

    f.write('#ifndef ' + header_guard + '\n#define ' + header_guard + '\n\n')
    f.write('class ' + class_name + '\n{\npublic:\n\t' + class_name + '();\n')
    f.write('\t~' + class_name + '();\nprivate:\n\n};\n\n#endif // ' + header_guard)

    f.close()

def write_to_cpp_file(class_name, file_path):
    f = open(file_path, "w+")

    f.write('#include \"' + class_name + '.h\"\n\n\n')
    f.write(class_name + '::' + class_name + '()\n{\n}\n\n\n')
    f.write(class_name + '::~' + class_name + '()\n{\n}\n')

    f.close()

if __name__ == '__main__':
   root = Tk()
   root.title('Class Creator')
   root.resizable(False, False)

   class_label = Label(root, text="Class Name")
   class_label.pack(side=LEFT)

   classname_box = Entry(root, bd=5)
   classname_box.pack(side=LEFT)
   classname_box.focus()

   folder_label = Label(root, text="Folder Path")
   folder_label.pack(side=LEFT)

   textbox = Entry(root, width=75, bd=5)
   textbox.pack(side=LEFT)

   browse_button = Button(root, text ="Browse", command=lambda: browse(textbox))
   browse_button.pack(side=LEFT)

   add_button = Button(root, text="Add Class", command=lambda: create_class_files(classname_box.get(), textbox.get()))
   add_button.pack(side=BOTTOM)

   root.mainloop()

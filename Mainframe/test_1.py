import tkinter
import tkinter.ttk
root = tkinter.Tk()
root.geometry('150x120')

def show():
    labelOther.config(text='Tkinter')
    labelOther.config(bg='lightgreen')

notebook = tkinter.ttk.Notebook(root)

frameOne = tkinter.Frame()
frameTwo = tkinter.Frame()

# 添加内容
label = tkinter.Label(frameOne, text='Python', bg='lightblue', fg='red')
label.pack(padx=10, pady=5)

button = tkinter.Button(frameTwo, text='请点击', command=show)
button.pack(padx=10, pady=5)

labelOther = tkinter.Label(frameTwo, fg='red')
labelOther.pack(padx=10, pady=5)

notebook.add(frameOne, text='选项卡1')
notebook.add(frameTwo, text='选项卡2')
notebook.pack(padx=10, pady=5, fill=tkinter.BOTH, expand=True)

root.mainloop()

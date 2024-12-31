from tkinter import ttk
from tkinter import messagebox as msg
import tkinter as tk
import requests
import json

class App:
    def __init__(self):
        self.rt = tk.Tk()
        self.rt.geometry("200x300")
        self.rt.title("Examination System")
        self.type = "NULL"
        self.name = "NULL"
        self.situ = False 
        self.add_problem_button = tk.Button(self.rt, text="Add Problem", command=lambda: (not self.situ) or self.add_problem_func())
        self.srh_problem_button = tk.Button(self.rt, text="Search", command=lambda: (not self.situ) or self.srh_problem_func())

        ###########################################
        self.lwin = tk.Toplevel(self.rt)
        self.lwin.protocol("WM_DELETE_WINDOW", lambda : None)
        def lwin_lgin_or_sgup(self: App):
            def pack():
                data = {}
                data["password"] = self.lwin_pswd_str.get()
                data["account"] = self.lwin_acnt_str.get()
                data["type"] = self.lwin_lgin_or_sgup_int.get()
                print(data)
                res = requests.post("http://localhost:8080/", json=json.dumps(data)).json()
                print(res)
                if res["ans"] == "ok":
                    self.type = res["type"]
                    self.name = self.lwin_acnt_str.get()
                    self.situ = True
                    self.lwin.destroy()
            return pack
        self.lwin_lgin_or_sgup_int = tk.IntVar()
        self.lwin_lgin_or_sgup_int.set(1)
        self.lwin_acnt_str = tk.StringVar()
        self.lwin_pswd_str = tk.StringVar()
        self.lwin_login_ra = tk.Radiobutton(self.lwin, text="Log in", value=1, variable=self.lwin_lgin_or_sgup_int)
        self.lwin_signp_ra = tk.Radiobutton(self.lwin, text="Sign up", value=2, variable=self.lwin_lgin_or_sgup_int)
        self.lwin_acnt_entry = tk.Entry(self.lwin, textvariable=self.lwin_acnt_str)
        self.lwin_acnt_entry.bind("<FocusIn>", self.tmp_focus_in(self.lwin_acnt_entry, "account here"))
        self.lwin_acnt_entry.bind("<FocusOut>", self.tmp_focus_out(self.lwin_acnt_entry, "account here"))
        self.lwin_pswd_entry = tk.Entry(self.lwin, textvariable=self.lwin_pswd_str)
        self.lwin_pswd_entry.bind("<FocusIn>", self.tmp_focus_in(self.lwin_pswd_entry, "password here"))
        self.lwin_pswd_entry.bind("<FocusOut>", self.tmp_focus_out(self.lwin_pswd_entry, "password here"))
        self.lwin_bt = tk.Button(self.lwin, text="Log in/Sign up", command=lwin_lgin_or_sgup(self))
        
        self.lwin_acnt_entry.pack()
        self.lwin_pswd_entry.pack()
        self.lwin_login_ra.pack()
        self.lwin_signp_ra.pack()
        self.lwin_bt.pack()
        # self.lwin.mainloop()
        ###########################################

        self.add_problem_button.pack()
        self.srh_problem_button.pack()

    def add_problem_func(self):
        if self.type == "Teacher":
            print("in")
            self.ap = tk.Toplevel(self.rt)
            self.ap.protocol("WM_DELETE_WINDOW", lambda : None)
            self.situ = False
            self.ap_problem_label = tk.Label(self.ap, text="Input problem below: ")
            self.ap_problem_str = tk.StringVar()
            self.ap_problem_entry = tk.Entry(self.ap, textvariable=self.ap_problem_str)
            def ap_exit(self: App):
                def pack():
                    self.situ = True
                    self.ap.destroy()
                return pack
            self.ap_exit_button = tk.Button(self.ap, text="Exit", command=ap_exit(self))
            def ap_submit(self: App):
                def pack():
                    data = {}
                    data["prob"] = self.ap_problem_str.get()
                    try:
                        eval(data["prob"])
                    except:
                        self.ap_problem_entry.delete(0, tk.END)
                        msg.showerror("Error", "format: <num1><operator><num2>, the only supported operator is +, -, *, /;")
                        return 
                    typedict = {"+": 1, "-": 2, "*": 3, "/": 4}
                    for opt in typedict:
                        if opt in data["prob"]:
                            data["type"] = typedict[opt]
                    if "type" not in data:
                        self.ap_problem_entry.delete(0, tk.END)
                        msg.showerror("Error", "format: <num1><operator><num2>, the only supported operator is +, -, *, /;")
                        return 
                    data["ans"] = eval(data["prob"])
                    # res = requests.post("http://localhost:8080/add/", json=json.dumps(data)).json()
                    # print(res)
                    # if res["ans"] != "ok":
                    #     msg.showerror("Error", "Add failed.")
                    print(data)
                return pack
            self.ap_submit_button = tk.Button(self.ap, text="Submit", command=ap_submit(self))

            self.ap_problem_label.pack()
            self.ap_problem_entry.pack()
            self.ap_submit_button.pack()
            self.ap_exit_button.pack()
            self.ap.mainloop()
        else:
            msg.showwarning("Teacher Only", "Add problem is not available for students! ")
    
    def srh_problem_func(self):
        if self.type == "Teacher":
            self.srh = tk.Toplevel(self.rt)
            self.srh.protocol("WM_DELETE_WINDOW", lambda : None)
            def srh_exit(self: App):
                def pack():
                    self.situ = True
                    self.srh.destroy()
                return pack
            self.srh_exit_button = tk.Button(self.srh, text="Exit", command=srh_exit(self))
            
        else:
            msg.showwarning("Teacher Only", "search problem is not available for students! ")

    def tmp_focus_in(self, etr: tk.Entry, df: str):
        def pack(event):
            if etr.get() == df:
                etr.delete(0, tk.END)
                etr.config(fg="black")
        return pack
    
    def tmp_focus_out(self, etr: tk.Entry, df: str):
        def pack(event):
            if not etr.get():
                etr.insert(0, df)
                etr.config(fg="grey")
        return pack

    def main(self):
        self.rt.mainloop()
        self.lwin.mainloop()

if __name__ == "__main__":
    app = App()
    app.main()
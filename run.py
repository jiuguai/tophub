import sys
import platform
if platform.node() == "zero_PC":
    sys.path.append(r"F:\QHJ\qhj\ZERO")
else:
    sys.path.append(r"D:\往期\QHJ\ZERO")
import importlib

func_path = "app.tophub_today.run"
module_name, func_name = func_path.rsplit(".",1)
module = importlib.import_module(module_name)
func = getattr(module, func_name)
func()







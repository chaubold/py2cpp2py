import testlib

def python_func():
	print("Hello from python!")
	return 7.0

a = testlib.MyObject("Peter")
print("My name is {}".format(a.get_name()))
a.call_python(python_func)
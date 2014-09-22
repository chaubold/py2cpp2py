py2cpp2py
=========
Showcases interopability between python and C++ using boost::python.

build & run
---------------
Use CMake in the testlib folder to configure and build the C++ module for python. It requires boost python, and currently the include path is hardcoded to python2.7. If you are not using 2.7, change that in `testlib/CMakeLists.txt`.

**Then copy the testlib binary (or create a symlink) into the same folder as runner.py, and rename it such that it is called** `testlib.so` **for Mac and Linux, or testlib.dll on Windows.**

Last but not least, run:
```
python runner.py
```

runner.py
---------------
Is a python script that imports the C++ library, creates an object defined via `boost::python`, and calls methods on that object. The most interesting call is the last one, where a python function is passed as an argument to the C++ method, which will then execute the python function from C++.

testlib/main.cpp
---------------
Contains the definition for the object `MyObject`, which is instanciated from the python script.
The last section defines the python interface to the C++ module. 

**Most interesting:** `MyObject::call_python` which does two things:

 1. Call the method that was passed from python
 2. Import the module `testlib` in python (so import itself), find the method called `print5` which was exposed from C++ to python as well, and call that.


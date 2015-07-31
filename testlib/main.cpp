#include <boost/python.hpp>
#include <iostream>

class MyObject{
public:
	MyObject(const std::string& n):
		name_(n)
	{}

	std::string get_name()
	{
		std::cout << "Hello from C++!" << std::endl;
		return name_;
	}

	void call_python(boost::python::object method)
	{
		using namespace boost::python;
		// call the passed method
		object py_result = method();
        double result = boost::python::extract<double>(py_result);

        std::cout << "Python method returned " << result << std::endl;

		// get an object defined in this lib
		object module = import("testlib");
		object print_method = module.attr("print5");
		print_method();
	}

private:
	std::string name_;
};

void print5()
{
	std::cout << "number 5" << std::endl;
}

BOOST_PYTHON_MODULE( testlib )
{
	using namespace boost::python;

	class_<MyObject>("MyObject", init<std::string>(args("name")))
      .def("get_name", &MyObject::get_name)
      .def("call_python", &MyObject::call_python)
      ;

    def("print5", print5);
}
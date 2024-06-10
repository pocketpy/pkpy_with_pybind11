#include "test.h"

void test_int() {
    py::object obj = py::int_(123);
    py::handle obj2 = py::eval("123");

    EXPECT_EQ(obj, obj2);

    EXPECT_EQ(obj.cast<int>(), 123);
    EXPECT_EQ(obj.cast<long>(), 123);
    EXPECT_EQ(obj.cast<long long>(), 123);
}

void test_float() {
    py::object obj = py::float_(123.0);
    py::handle obj2 = py::eval("123.0");

    EXPECT_EQ(obj, obj2);

    EXPECT_EQ(obj.cast<float>(), 123.0);
    EXPECT_EQ(obj.cast<double>(), 123.0);
}

void test_str() {
    py::object obj = py::str("123");
    py::handle obj2 = py::eval("'123'");

    EXPECT_EQ(obj, obj2);

    EXPECT_STREQ(obj.cast<char*>(), "123");
    EXPECT_STREQ(obj.cast<const char*>(), "123");
    EXPECT_EQ(obj.cast<std::string>(), "123");
    EXPECT_EQ(obj.cast<std::string_view>(), "123");
}

void test_tuple() {
    py::tuple tuple = py::tuple(1, "123", 3);
    EXPECT_EQ(tuple, py::eval("(1, '123', 3)"));
    EXPECT_EQ(tuple.size(), 3);
    EXPECT_FALSE(tuple.empty());

    tuple[0] = py::int_(3);
    tuple[2] = py::int_(1);
    EXPECT_EQ(tuple, py::eval("(3, '123', 1)"));
}

void test_list() {
    // test constructors
    py::list list = py::list();
    EXPECT_EQ(list, py::eval("[]"));
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());

    list = py::list(1, 2, 3);
    EXPECT_EQ(list, py::eval("[1, 2, 3]"));
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());

    // test accessor
    list[0] = py::int_(3);
    list[2] = py::int_(1);
    EXPECT_EQ(list, py::eval("[3, 2, 1]"));

    // test other apis
    list.append(py::int_(4));
    EXPECT_EQ(list, py::eval("[3, 2, 1, 4]"));

    list.extend(py::list(5, 6));
    EXPECT_EQ(list, py::eval("[3, 2, 1, 4, 5, 6]"));

    list.insert(0, py::int_(7));
    EXPECT_EQ(list, py::eval("[7, 3, 2, 1, 4, 5, 6]"));
}

void test_dict() {
    // test constructors
    py::dict dict = py::dict();
    EXPECT_EQ(dict, py::eval("{}"));
    EXPECT_EQ(dict.size(), 0);
    EXPECT_TRUE(dict.empty());

    // test accessor
    dict["a"] = py::int_(1);
    dict["b"] = py::int_(2);
    dict["c"] = py::int_(3);
    EXPECT_EQ(dict, py::eval("{'a': 1, 'b': 2, 'c': 3}"));

    // test other apis
    dict.clear();
    EXPECT_EQ(dict, py::eval("{}"));
}

TEST(pybind11, types) {
    py::initialize();

    test_int();
    test_float();
    test_str();
    test_tuple();
    test_list();
    test_dict();

    py::finalize();
}

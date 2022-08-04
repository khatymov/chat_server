#pragma once

#include <gmock/gmock.h>

#include "my_class.h"

class MockMyClass: public MyClass
{
public:
    MOCK_METHOD(std::string, get, (), (const, override));
};

class MyClassRunner: public MyClass
{
public:
    void call_methods(MyClass& my_class)
    {
        my_class.get();
    }
};
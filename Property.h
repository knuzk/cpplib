// Property.h

#pragma once

template <class T, class Container>
class SimpleProperty
{
public:
    SimpleProperty() {}
    SimpleProperty(T&& value) : value(value) {}

protected:
    friend Container;
    T value;
};

#define PROPERTIES_BEGIN(Container) \
public: \
    using PropertyContainer=Container; \
    class Property \
    { \
    public: \
        Property(PropertyContainer* self) : self(self) {} \
    protected: \
        PropertyContainer* self; \
    };

#define PROPERTIES_END() private:

#define PROPERTY_GETSET_2_(T, name) \
    class : public SimpleProperty<T, PropertyContainer> \
    { \
    public: \
        using SimpleProperty<T, PropertyContainer>::SimpleProperty; \
        operator const T() const { return this->value; }; \
        void operator= (T&& value) { this->value = value; }; \
    } name

#define PROPERTY_GET_2_(T, name) \
    class : public SimpleProperty<T, PropertyContainer> \
    { \
    public: \
        using SimpleProperty<T, PropertyContainer>::SimpleProperty; \
        operator const T() const { return this->value; }; \
    } name

#define PROPERTY_SET_2_(T, name) \
    class : public SimpleProperty<T, PropertyContainer> \
    { \
    public: \
        using SimpleProperty<T, PropertyContainer>::SimpleProperty; \
        void operator= (T&& value) { this->value = value; } \
    } name

#define PROPERTY_GETSET_4_(T, name, getter, setter) \
    class : public Property \
    { \
    public: \
        using Property::Property; \
        operator const T() const getter; \
        void operator= (T&& value) setter; \
    } name

#define PROPERTY_GET_3_(T, name, getter) \
    class : public Property \
    { \
    public: \
        using Property::Property; \
        operator const T() const getter; \
    } name

#define PROPERTY_SET_3_(T, name, setter) \
    class : public Property \
    { \
    public: \
        using Property::Property; \
        void operator= (T&& value) setter; \
    } name

#define PROPERTY_GETSET_(_1, _2, _3, _4, NAME,...) NAME
#define PROPERTY_GETSET(...) \
    PROPERTY_GETSET_(__VA_ARGS__, PROPERTY_GETSET_4_, NA, PROPERTY_GETSET_2_)(__VA_ARGS__)
#define PROPERTY_GET(...) \
    PROPERTY_GETSET_(__VA_ARGS__, NA, PROPERTY_GET_3_, PROPERTY_GET_2_)(__VA_ARGS__)
#define PROPERTY_SET(...) \
    PROPERTY_GETSET_(__VA_ARGS__, NA, PROPERTY_SET_3_, PROPERTY_SET_2_)(__VA_ARGS__)


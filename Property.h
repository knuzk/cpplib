// Property.h

#pragma once

enum class PropertyType
{
    GETSET,
    GET,
    SET,
};

template <class T, class Container, PropertyType type>
class SimpleProperty;

template <class T, class Container>
class SimpleProperty<T, Container, PropertyType::GETSET>
{
public:
    SimpleProperty() {}
    SimpleProperty(T&& value) : value(value) {}

    operator const T() const { return this->value; };
    void operator= (T&& value) { this->value = value; };

protected:
    friend Container;
    T value;
};

template <class T, class Container>
class SimpleProperty<T, Container, PropertyType::GET>
: public SimpleProperty<T, Container, PropertyType::GETSET>
{
public:
    using SimpleProperty<T, Container, PropertyType::GETSET>::SimpleProperty;
    void operator= (T&& value) = delete;
};

template <class T, class Container>
class SimpleProperty<T, Container, PropertyType::SET>
: public SimpleProperty<T, Container, PropertyType::GETSET>
{
public:
    using SimpleProperty<T, Container, PropertyType::GETSET>::SimpleProperty;
    operator const T() const = delete;
};

template <class Container>
class Property
{
public:
    Property(Container* self) : self(self) {}

protected:
    Container* self; 
};

#define PROPERTIES_BEGIN(Container) \
public: \
    using PropertyContainer=Container;

#define PROPERTIES_END() private:

#define PROPERTY_GETSET_2_(T, name) \
    SimpleProperty<T, PropertyContainer, PropertyType::GETSET> name

#define PROPERTY_GET_2_(T, name) \
    SimpleProperty<T, PropertyContainer, PropertyType::GET> name

#define PROPERTY_SET_2_(T, name) \
    SimpleProperty<T, PropertyContainer, PropertyType::SET> name

#define PROPERTY_GETSET_4_(T, name, getter, setter) \
    class : public Property<PropertyContainer> \
    { \
    public: \
        using Property<PropertyContainer>::Property; \
        operator const T() const getter; \
        void operator= (T&& value) setter; \
    } name

#define PROPERTY_GET_3_(T, name, getter) \
    class : public Property<PropertyContainer> \
    { \
    public: \
        using Property<PropertyContainer>::Property; \
        operator const T() const getter; \
    } name

#define PROPERTY_SET_3_(T, name, setter) \
    class : public Property<PropertyContainer> \
    { \
    public: \
        using Property<PropertyContainer>::Property; \
        void operator= (T&& value) setter; \
    } name

#define PROPERTY_GETSET_(_1, _2, _3, _4, NAME,...) NAME
#define PROPERTY_GETSET(...) \
    PROPERTY_GETSET_(__VA_ARGS__, PROPERTY_GETSET_4_, NA, PROPERTY_GETSET_2_)(__VA_ARGS__)
#define PROPERTY_GET(...) \
    PROPERTY_GETSET_(__VA_ARGS__, NA, PROPERTY_GET_3_, PROPERTY_GET_2_)(__VA_ARGS__)
#define PROPERTY_SET(...) \
    PROPERTY_GETSET_(__VA_ARGS__, NA, PROPERTY_SET_3_, PROPERTY_SET_2_)(__VA_ARGS__)


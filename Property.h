// Property.h

#pragma once

enum PropertyType
{
    Property_GetSet,
    Property_GetOnly,
    Property_SetOnly
};

template <class T, class Container, PropertyType type>
class SimpleProperty
{
};

template <class T, class Container>
class SimpleProperty<T, Container, Property_GetSet>
{
public:
    SimpleProperty()
    {
    }

    SimpleProperty(T&& value)
    {
        this->value = value;
    }

    void operator= (T&& value)
    {
        this->value = value;
    }

    operator T() const
    {
        return this->value;
    }

private:
    friend Container;

    T value;
};

template <class T, class Container>
class SimpleProperty<T, Container, Property_GetOnly>
{
public:
    SimpleProperty()
    {
    }

    SimpleProperty(T&& value)
    {
        this->value = value;
    }

    operator T() const
    {
        return this->value;
    }

private:
    friend Container;

    T value;
};

template <class T, class Container>
class SimpleProperty<T, Container, Property_SetOnly>
{
public:
    SimpleProperty()
    {
    }

    SimpleProperty(T&& value)
    {
        this->value = value;
    }

    void operator= (T&& value)
    {
        this->value = value;
    }

private:
    friend Container;

    T value;
};

template <class T, class Container, class GetterSetter, PropertyType type>
class Property
{
};

template <class T, class Container, class GetterSetter>
class Property<T, Container, GetterSetter, Property_GetSet>
{
public:
    Property()
    {
    }

    Property(T&& value)
    {
        this->value = value;
    }

    void operator= (T&& value)
    {
        Container* self = GetterSetter::ToSelf((size_t)this);
        GetterSetter::Set(self, value);
    }

    operator T() const
    {
        Container* self = GetterSetter::ToSelf((size_t)this);
        return GetterSetter::Get(self);
    }

private:
    friend Container;

    T value;
};

template <class T, class Container, class GetterSetter>
class Property<T, Container, GetterSetter, Property_GetOnly>
{
public:
    Property()
    {
    }

    Property(T&& value)
    {
        this->value = value;
    }

    void operator= (T&& value)
    {
        Container* self = GetterSetter::ToSelf((size_t)this);
        GetterSetter::Set(self, value);
    }

private:
    friend Container;

    T value;
};

template <class T, class Container, class GetterSetter>
class Property<T, Container, GetterSetter, Property_SetOnly>
{
public:
    Property()
    {
    }

    Property(T&& value)
    {
        this->value = value;
    }

    operator T() const
    {
        Container* self = GetterSetter::ToSelf((size_t)this);
        return GetterSetter::Get(self);
    }

private:
    friend Container;

    T value;
};

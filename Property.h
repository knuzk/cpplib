// Property.h

enum PropertyType
{
    Property_GetSet,
    Property_GetOnly,
    Property_SetOnly
};

template <class T, PropertyType type>
class SimpleProperty
{
};

template <class T>
class SimpleProperty<T, Property_GetSet>
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

public:
    T value;
};

template <class T>
class SimpleProperty<T, Property_GetOnly>
{
public:
    SimpleProperty(T& value)
    : value(value)
    {
    }

    operator T() const
    {
        return this->value;
    }

private:
    T& value;
};

template <class T>
class SimpleProperty<T, Property_SetOnly>
{
public:
    SimpleProperty(T& value)
    : value(value)
    {
    }

    void operator= (T&& value)
    {
        this->value = value;
    }

private:
    T& value;
};

template <class T, class Container, class GetterSetter, PropertyType type>
class Property
{
};

template <class T, class Container, class GetterSetter>
class Property<T, Container, GetterSetter, Property_GetSet>
{
public:
    Property(Container* self)
    : self(self)
    {
    }

    void operator= (T&& value)
    {
        GetterSetter::Set(this->self, value);
    }

    operator T() const
    {
        return GetterSetter::Get(this->self);
    }

private:
    Container* self;
};

template <class T, class Container, class GetterSetter>
class Property<T, Container, GetterSetter, Property_GetOnly>
{
public:
    Property(Container* self)
    : self(self)
    {
    }

    operator T() const
    {
        return GetterSetter::Get(this->self);
    }

private:
    Container* self;
};

template <class T, class Container, class GetterSetter>
class Property<T, Container, GetterSetter, Property_SetOnly>
{
public:
    Property(Container* self)
    : self(self)
    {
    }

    void operator= (T&& value)
    {
        GetterSetter::Set(this->self, value);
    }

private:
    Container* self;
};

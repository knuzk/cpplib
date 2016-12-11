// Property.h

enum PropertyType
{
    PropertyType_SimpleGetSet,
};

template <class T, PropertyType type>
class Property
{
};

template <class T>
class Property<T, PropertyType_SimpleGetSet>
{
public:
    Property()
    {
    }

    Property(T&& value)
    {
        this->value = value;
    }

    T& operator= (T&& value)
    {
        this->value = value;
        return this->value;
    }

    operator T() const
    {
        return this->value;
    }

    operator T&()
    {
        return this->value;
    }

private:
    T value;
};
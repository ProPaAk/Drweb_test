#include <iostream>
#include <map>
#include <exception>
#include <string>

//------------------------------------------------------------

template<class Key, class Value>
class Dictionary{
public:
    virtual ~Dictionary() = default;

    virtual const Value& get(const Key& key) const = 0;
    virtual void set(const Key& key, const Value& value) = 0;
    virtual bool is_set(const Key& key) const = 0;
};

//------------------------------------------------------------

template<class Key>
class Not_found_exception : public std::exception{
public:
    virtual const Key& get_key() const noexcept = 0;
};

//------------------------------------------------------------

template<class TKey>
class MyNotFoundException : public Not_found_exception<TKey>{
	TKey key;
public:
	MyNotFoundException(const TKey& key) : key(key) {}

	const TKey& get_key() const noexcept override{
		return key;
	}
};

//------------------------------------------------------------

template<class TKey, class TValue>
class MyDictionary : public Dictionary<TKey, TValue> {
	std::map<TKey, TValue> myMap;

public:
	const TValue& get(const TKey& key) const override{
		auto it = myMap.find(key);
		if (it == myMap.end())
			throw MyNotFoundException<TKey>(key);
		return it->second;
	}

	void set(const TKey& key, const TValue& value) override{
		myMap[key] = value;
	}

	bool is_set(const TKey& key) const override{
		return myMap.find(key) != myMap.end();
	}
};

//------------------------------------------------------------

int main(){
    MyDictionary<std::string, int> d;
	d.set("Hello", 1);
	d.set("Cucumber", 11);
	d.set("21", 21);
	try{
		std::cout << d.get("Hello") << '\n';
		std::cout << d.get("21") << '\n';
		std::cout << d.get("Cucumber Rick") << '\n';
	}
	catch (const MyNotFoundException<std::string> &e){
		std::cout << "Error: key " << e.get_key() << " not found." << '\n';
	}
    return 0;
}
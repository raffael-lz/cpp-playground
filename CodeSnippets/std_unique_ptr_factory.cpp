/* g++ -std=c++14 std_unique_ptr_factory.cpp -o bin/std_unique_ptr_factory */

#include <iostream>
#include <memory>

// Create base + child classes

struct Mammal
{
	Mammal() { std::cout << " Mammal::Mammal()" << std::endl; };
	virtual ~Mammal() { std::cout << " ~Mammal::Mammal()" << std::endl; };
	virtual void Iam() { std::cout << " I am mammal" << std::endl; };
};

struct Cat : public Mammal
{
	Cat() { std::cout << " Cat::Cat()" << std::endl; };
	~Cat() { std::cout << " ~Cat::Cat()" << std::endl; };
	void Iam() { std::cout << " I am a cat" << std::endl; };
};

struct Dog : public Mammal
{
	Dog() { std::cout << " Dog::Dog()" << std::endl; };
	~Dog() { std::cout << " ~Dog::Dog()" << std::endl; };
	void Iam() { std::cout << " I am a dog" << std::endl; };
};

struct Dolphin : public Mammal
{
	Dolphin() { std::cout << " Dolhpin::Dolphin()" << std::endl; };
	~Dolphin() { std::cout << " ~Dolphin::Dolphin()" << std::endl; };
	void Iam() { std::cout << " I am a dolphin" << std::endl; };
};

// Create factory method which returns depending on type a unique_ptr with custom deleter.
template <typename T, typename D,  typename... Ts>
auto MakeMammal(D d, Ts&&... params)
{
	return std::unique_ptr<T,D>(new T(std::forward<Ts>(params)...), d);
}

int main()
{
	auto custom_deleter = [](Mammal * m)
			{
				std::cout << " Custom deleter with Mammal obj: ";
				m->Iam();
				delete m;
			};
	auto custom_deleter_dog = [](Dog * d)
			{
				std::cout << " Custom deleter with Dog obj: ";
				d->Iam();
				delete d;
			};

	std::cout << "Creating objects: " << std::endl;
	std::unique_ptr<Mammal, decltype(custom_deleter)> m_1 = MakeMammal<Cat>(custom_deleter);
	auto m_2 = MakeMammal<Dolphin>(custom_deleter);
	auto m_3 = MakeMammal<Dog>(custom_deleter);
	auto d_1 = MakeMammal<Dog>(custom_deleter_dog);

	std::unique_ptr<Mammal, decltype(custom_deleter)> m_4(new Cat, custom_deleter);

	std::cout << "What am I: " << std::endl;

	std::cout << "m_1: ";
	m_1->Iam();
	std::cout << "m_2: ";
	m_2->Iam();
	std::cout << "m_3: ";
	m_3->Iam();
	std::cout << "d_1: ";
	d_1->Iam();
	std::cout << "m_4: ";
	m_4->Iam();
}
